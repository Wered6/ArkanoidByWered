// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPaddle.h"
#include "ArkanoidByWered/Settings/ABWUserSettings.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AABWPaddle::AABWPaddle()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionProfileName(TEXT("BlockAll"));

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->SetupAttachment(CollisionComp);
	SpriteComp->SetCollisionProfileName(TEXT("NoCollision"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void AABWPaddle::BeginPlay()
{
	Super::BeginPlay();

	GameSettings = Cast<UABWUserSettings>(GEngine->GetGameUserSettings());

	SetDefaultSprite();
}

float AABWPaddle::GetCollisionWidth() const
{
	if (!CollisionComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPaddle::GetCollisionWidth|CollisionComp is null"));
		return -1.f;
	}

	return CollisionComp->GetUnscaledBoxExtent().X * 2.f;
}

float AABWPaddle::GetCollisionHeight() const
{
	if (!CollisionComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPaddle::GetCollisionWidth|CollisionComp is null"));
		return -1.f;
	}

	return CollisionComp->GetUnscaledBoxExtent().Z * 2.f;
}

void AABWPaddle::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AABWPaddle::SetDefaultSprite() const
{
	if (!GameSettings)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPaddle::SetDefaultSprite|GameSettings is null"));
		return;
	}

	GameSettings->LoadSettings();

	if (!SpriteComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPaddle::SetDefaultSprite|SpriteComp is null"));
		return;
	}

	SpriteComp->SetSprite(GameSettings->SelectedPaddle);
}
