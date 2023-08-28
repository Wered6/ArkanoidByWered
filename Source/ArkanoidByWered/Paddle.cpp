// Copyright (c) 2023 Wered. All rights reserved.


#include "Paddle.h"
#include "ABWUserSettings.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APaddle::APaddle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionProfileName(TEXT("BlockAll"));

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->SetupAttachment(CollisionComp);
	SpriteComp->SetCollisionProfileName(TEXT("NoCollision"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	SetDefaultSprite();
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float APaddle::GetCollisionWidth() const
{
	return CollisionComp->GetUnscaledBoxExtent().X * 2.f;
}

float APaddle::GetCollisionHeight() const
{
	return CollisionComp->GetUnscaledBoxExtent().Z * 2.f;
}

void APaddle::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void APaddle::SetDefaultSprite() const
{
	UABWUserSettings* GameSettings = Cast<UABWUserSettings>(GEngine->GetGameUserSettings());
	if (GameSettings)
	{
		GameSettings->LoadSettings();

		if (SpriteComp)
		{
			SpriteComp->SetSprite(GameSettings->SelectedPaddle);
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
