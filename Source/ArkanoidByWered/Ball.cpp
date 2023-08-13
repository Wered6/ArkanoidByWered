// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Paddle.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->SetupAttachment(CollisionComp);

	// Initial VelocityVector
	VelocityVector = {0, 0, -1} * Speed;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set the ball in motion, taking delta time into account and enable collision
	const FVector Movement = VelocityVector * DeltaTime;
	AddActorLocalOffset(Movement, true);
}

void ABall::UpdateVelocityVector(const float X, const float Z)
{
	VelocityVector = {X, 0, Z};
}

void ABall::BounceBall(AActor* HitActor, const FVector& HitLocation)
{
	BounceOffPaddle(HitActor, HitLocation);
	// or bounceoffwall
}

float ABall::CalculateBounceAngle(const float RelativeHitLocationX, const float BallPaddleHalfWidth) const
{
	constexpr float MaximumDeviation{45.f};
	constexpr float AngleOffset{90.f};

	const float Angle = RelativeHitLocationX / BallPaddleHalfWidth * MaximumDeviation;

	return AngleOffset - Angle;
}

void ABall::BounceOffPaddle(AActor* HitActor, const FVector& HitLocation)
{
	// Attempt to cast to APaddle
	const APaddle* Paddle = Cast<APaddle>(HitActor);
	// Check if cast failed
	if (!Paddle)
	{
		UE_LOG(LogTemp, Warning, TEXT("BounceBall wasn't called with a Ball actor."));
		return;
	}

	// Calculate half width for bounce calculations
	const float BallPaddleHalfWidth = CollisionComp->GetUnscaledBoxExtent().X + Paddle->GetCollisionWidth() / 2;
	// Check for near-zero width
	if (FMath::IsNearlyZero(BallPaddleHalfWidth))
	{
		UE_LOG(LogTemp, Warning, TEXT("Width is near zero."));
		return;
	}

	// Calculate relative hit on X-axis
	const float RelativeHitLocationX = HitLocation.X - Paddle->GetActorLocation().X;

	// Calculate bounce angle
	const float BounceAngle = CalculateBounceAngle(RelativeHitLocationX, BallPaddleHalfWidth);

	// Calculate and update ball velocity
	const float Radians = FMath::DegreesToRadians(BounceAngle);
	const float XValue = Speed * FMath::Cos(Radians);
	const float ZValue = Speed * FMath::Sin(Radians);
	UpdateVelocityVector(XValue, ZValue);
}
