// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "ArkanoidByWeredUserSettings.h"
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
	CollisionComp->SetCollisionProfileName(TEXT("BlockAll"));

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->SetupAttachment(CollisionComp);
	SpriteComp->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	VelocityVector = VelocityVector * BallSpeed;
	
	SetDefaultSprite();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Movement = VelocityVector * DeltaTime;
	AddActorLocalOffset(Movement, true);
}

void ABall::BounceBall(const FVector& HitLocation, const FVector& HitNormal, AActor* HitActor)
{
	const APaddle* HitPaddle = Cast<APaddle>(HitActor);
	if (HitPaddle)
	{
		BounceOffPaddle(HitPaddle, HitLocation);
	}
	else
	{
		BounceOffWall(HitNormal);
	}
}

void ABall::BounceOffPaddle(const APaddle* Paddle, const FVector& HitLocation)
{
	const float BallAndPaddleHalfWidth = CollisionComp->GetUnscaledBoxExtent().X + Paddle->GetCollisionWidth() / 2;
	// Determine hit position on paddle (0.0 = leftmost, 1.0 = rightmost)
	const float HitPosition = (HitLocation.X - Paddle->GetActorLocation().X + BallAndPaddleHalfWidth) / (
		BallAndPaddleHalfWidth * 2);

	const float Radians = FMath::DegreesToRadians(Angle);
	const float XValue{FMath::Cos(Radians)};
	const float ZValue{FMath::Sin(Radians)};

	const FVector LeftmostBounceDirection{-XValue, 0, ZValue};
	const FVector RightmostBounceDirection{XValue, 0, ZValue};

	FVector NewDirection = FMath::Lerp(LeftmostBounceDirection, RightmostBounceDirection, HitPosition);
	NewDirection.Normalize();
	VelocityVector = NewDirection * BallSpeed;
}

void ABall::BounceOffWall(const FVector& HitNormal)
{
	if (FMath::IsNearlyEqual(HitNormal.Z, -1.f, 0.01f) || FMath::IsNearlyEqual(HitNormal.Z, 1.f, 0.01f))
	{
		// Reverse vertical velocity for top/bottom walls
		VelocityVector.Z = -VelocityVector.Z;
	}
	else
	{
		// Reverse horizontal velocity for side walls
		VelocityVector.X = -VelocityVector.X;
	}
	VelocityVector.Normalize();
	VelocityVector = VelocityVector * BallSpeed;
}

void ABall::SetDefaultSprite() const
{
	UArkanoidByWeredUserSettings* GameSettings = Cast<UArkanoidByWeredUserSettings>(GEngine->GetGameUserSettings());
	if (GameSettings)
	{
		GameSettings->LoadSettings();

		if (SpriteComp)
		{
			SpriteComp->SetSprite(GameSettings->SelectedBall);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpriteComp is not valid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameSettings is not valid"));
	}
}
