// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWBrick.h"
#include "ABWBall.h"
#include "ArkanoidByWered/GameModes/ABWGameModeBase.h"
#include "PaperSpriteComponent.h"

// Sets default values
AABWBrick::AABWBrick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MainSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Main Sprite"));
	RootComponent = MainSpriteComp;
	MainSpriteComp->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void AABWBrick::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());

	OnActorHit.AddDynamic(this, &AABWBrick::HandleOnHit);
}

// Called every frame
void AABWBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABWBrick::HandleOnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(AABWBall::StaticClass()))
	{
		if (NumOfHits < BrokenBrickSprites.Num() && BrokenBrickSprites[NumOfHits] != nullptr)
		{
			MainSpriteComp->SetSprite(BrokenBrickSprites[NumOfHits]);
		}
		else
		{
			// todo add sound and maybe some animation
			Destroy();
			GameMode->BrickWasDestroyed();
		}
		NumOfHits++;
	}
}
