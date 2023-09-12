// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWBall.h"
#include "ArkanoidByWered/GameModes/ABWGameModeBase.h"
#include "ABWPaddle.h"
#include "PaperSpriteComponent.h"
#include "ArkanoidByWered/SaveGame/ABWCustomizationSaveGame.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"

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

	Deactivate();
}

void AABWBall::Activate()
{
	SetActorTickEnabled(true);
	SpriteComp->SetVisibility(true);
	CollisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	CollisionComp->SetSimulatePhysics(true);
}

void AABWBall::Deactivate()
{
	SetActorTickEnabled(false);
	SpriteComp->SetVisibility(false);
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetCollisionProfileName(TEXT("NoCollision"));
	SetActorLocation(FVector::ZeroVector);
	bIsLaunched = false;
}

void AABWBall::BeginPlay()
{
	Super::BeginPlay();

	Init();
	SetDefaultSprite();
	check(CheckNullPointers());
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
		GameMode->HandleBallDestruction(this);
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

void AABWBall::Init()
{
	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());
	LoadGameInstance = Cast<UABWCustomizationSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
	if (!LoadGameInstance)
	{
		LoadGameInstance = Cast<UABWCustomizationSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UABWCustomizationSaveGame::StaticClass()));
	}
}

void AABWBall::SetDefaultSprite() const
{
	SpriteComp->SetSprite(LoadGameInstance->GetBallSprite());
}

bool AABWBall::CheckNullPointers() const
{
	if (!CollisionComp)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWBall::CheckNullPointers|CollisionComp is null"));
		return false;
	}
	if (!SpriteComp)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWBall::CheckNullPointers|SpriteComp is null"));
		return false;
	}
	if (!GameMode)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWBall::CheckNullPointers|GameMode is null"));
		return false;
	}
	if (!LoadGameInstance)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWBall::CheckNullPointers|LoadGameInstance is null"));
		return false;
	}
	return true;
}
