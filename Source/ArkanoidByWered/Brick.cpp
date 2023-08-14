// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABrick::ABrick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionProfileName(TEXT("BlockAll"));

	MainSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Main Sprite"));
	MainSpriteComp->SetupAttachment(CollisionComp);
	MainSpriteComp->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrick::OnBallHitBrick()
{
	NumOfHits++;
	if (NumOfHits < Sprites.Num() && Sprites[NumOfHits] != nullptr)
	{
		MainSpriteComp->SetSprite(Sprites[NumOfHits]);
	}
	else
	{
		Destroy();
	}
}
