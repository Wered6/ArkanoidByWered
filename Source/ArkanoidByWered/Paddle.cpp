// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APaddle::APaddle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->SetupAttachment(CollisionComp);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &APaddle::MoveHorizontal);
}

void APaddle::BounceBall(AActor* OtherActor, const FVector& HitLocation)
{
	// Attempt to cast to ABall
	ABall* Ball = Cast<ABall>(OtherActor);
	// Check if cast failed
	if (!Ball)
	{
		UE_LOG(LogTemp, Warning, TEXT("BounceBall wasn't called with a Ball actor."));
		return;
	}

	// Calculate half width for bounce calculations
	const float BallPaddleHalfWidth = CollisionComp->GetUnscaledBoxExtent().X + Ball->GetWidth() / 2;
	// Check for near-zero width
	if (FMath::IsNearlyZero(BallPaddleHalfWidth))
	{
		UE_LOG(LogTemp, Warning, TEXT("Width is near zero."));
		return;
	}

	// Calculate relative hit on X-axis
	const float RelativeHitLocationX = HitLocation.X - GetActorLocation().X;

	// Calculate bounce angle
	const float BounceAngle = CalculateBounceAngle(RelativeHitLocationX, BallPaddleHalfWidth);

	// Get ball speed
	const float Speed = Ball->GetVelocityVector().Size();
	// Check for near-zero ball speed
	if (FMath::IsNearlyZero(Speed))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball speed is near zero."));
		return;
	}

	// Calculate and update ball velocity
	UpdateBallVelocity(Ball, BounceAngle, Speed);
}


void APaddle::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

float APaddle::CalculateBounceAngle(const float RelativeHitLocationX, const float BallPaddleHalfWidth) const
{
	const float Angle = RelativeHitLocationX / BallPaddleHalfWidth * 45.f;
	constexpr float AngleOffset{90.f};
	return AngleOffset - Angle;
}

void APaddle::UpdateBallVelocity(ABall* Ball, const float BounceAngle, const float Speed) const
{
	const float Radians = FMath::DegreesToRadians(BounceAngle);
	const float XValue = Speed * FMath::Cos(Radians);
	const float ZValue = Speed * FMath::Sin(Radians);
	Ball->UpdateVelocityVector(XValue, ZValue);
}
