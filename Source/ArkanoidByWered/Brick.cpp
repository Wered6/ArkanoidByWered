// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABrick::ABrick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Main Sprite"));
	RootComponent = MainSpriteComp;
	MainSpriteComp->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ABrick::HandleOnHit);
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrick::HandleOnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (NumOfHits < BrokeBrickSprites.Num() && BrokeBrickSprites[NumOfHits] != nullptr)
	{
		MainSpriteComp->SetSprite(BrokeBrickSprites[NumOfHits++]);
	}
	else
	{
		Destroy();
	}
}
