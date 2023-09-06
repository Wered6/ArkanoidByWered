// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWBall.h"
#include "ArkanoidByWered/GameModes/ABWGameModeBase.h"
#include "ArkanoidByWered/Settings/ABWUserSettings.h"
#include "ABWPaddle.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"

AABWBall::AABWBall()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionProfileName(TEXT("BlockAll"));

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->SetupAttachment(CollisionComp);
	SpriteComp->SetCollisionProfileName(TEXT("NoCollision"));

	VelocityVector = InitialVelocityVector * InitialBallSpeed;
}

void AABWBall::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());
	GameSettings = Cast<UABWUserSettings>(GEngine->GetGameUserSettings());

	SetDefaultSprite();
}

void AABWBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Movement = VelocityVector * DeltaTime;
	AddActorLocalOffset(Movement, true);
}

void AABWBall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(ATriggerBox::StaticClass()))
	{
		Destroy();

		if (!GameMode)
		{
			UE_LOG(LogTemp, Warning, TEXT("AABWBall::NotifyActorBeginOverlap|GameMode is null"));
		}

		GameMode->BallWasDestroyed();
	}
}

float AABWBall::GetCollisionHeight() const
{
	return CollisionComp->GetUnscaledBoxExtent().Z * 2.f;
}

void AABWBall::BounceBall(const FVector& HitLocation, const FVector& HitNormal, AActor* HitActor)
{
	const AABWPaddle* HitPaddle = Cast<AABWPaddle>(HitActor);
	if (HitPaddle)
	{
		BounceOffPaddle(HitPaddle, HitLocation);
	}
	else
	{
		BounceOffWall(HitNormal);
	}
}

void AABWBall::LaunchBall()
{
	if (!bIsLaunched)
	{
		bIsLaunched = true;
		VelocityVector = InitialVelocityVector * BallSpeed;
	}
}

void AABWBall::BounceOffPaddle(const AABWPaddle* Paddle, const FVector& HitLocation)
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

	const float ModificatedPosition = HitPosition + FMath::FRandRange(-0.1f, 0.1f);

	FVector NewDirection = FMath::Lerp(LeftmostBounceDirection, RightmostBounceDirection, ModificatedPosition);
	NewDirection.Normalize();

	VelocityVector = NewDirection * BallSpeed;
}

void AABWBall::BounceOffWall(const FVector& HitNormal)
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

void AABWBall::SetDefaultSprite() const
{
	if (!GameSettings)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWBall::SetDefaultSprite|GameSettings is null"));
		return;
	}

	GameSettings->LoadSettings();

	if (!SpriteComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWBall::SetDefaultSprite|SpriteComp is null"));
		return;
	}

	SpriteComp->SetSprite(GameSettings->SelectedBall);
}
