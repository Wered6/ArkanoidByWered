// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "ArkanoidByWeredUserSettings.h"
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
	
	UArkanoidByWeredUserSettings* GameSettings = Cast<UArkanoidByWeredUserSettings>(GEngine->GetGameUserSettings());
	if(GameSettings)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameSettings is valid"));
		GameSettings->LoadSettings();
    
		if(SpriteComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpriteComp is valid"));
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

float APaddle::GetCollisionWidth() const
{
	return CollisionComp->GetUnscaledBoxExtent().X * 2.f;
}


void APaddle::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}
