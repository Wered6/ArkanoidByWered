// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPaddle.h"
#include "PaperSpriteComponent.h"
#include "ArkanoidByWered/SaveGame/ABWCustomizationSaveGame.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

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

	Init();
	SetDefaultSprite();
	check(CheckNullPointers());
}

float AABWPaddle::GetCollisionWidth() const
{
	return CollisionComp->GetUnscaledBoxExtent().X * 2.f;
}

float AABWPaddle::GetCollisionHeight() const
{
	return CollisionComp->GetUnscaledBoxExtent().Z * 2.f;
}

void AABWPaddle::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AABWPaddle::Init()
{
	LoadGameInstance = Cast<UABWCustomizationSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
	if (!LoadGameInstance)
	{
		LoadGameInstance = Cast<UABWCustomizationSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UABWCustomizationSaveGame::StaticClass()));
	}
}

void AABWPaddle::SetDefaultSprite() const
{
	SpriteComp->SetSprite(LoadGameInstance->GetPaddleSprite());
}

bool AABWPaddle::CheckNullPointers() const
{
	if (!CollisionComp)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWPaddle::CheckNullPointers|CollisionComp is null"));
		return false;
	}
	if (!SpriteComp)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWPaddle::CheckNullPointers|SpriteComp is null"));
		return false;
	}
	if (!FloatingPawnMovement)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWPaddle::CheckNullPointers|FloatingPawnMovement is null"));
		return false;
	}
	if (!LoadGameInstance)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWPaddle::CheckNullPointers|LoadGameInstance is null"));
		return false;
	}
	return true;
}