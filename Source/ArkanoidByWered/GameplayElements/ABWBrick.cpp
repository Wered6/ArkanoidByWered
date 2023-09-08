// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWBrick.h"
#include "ABWBall.h"
#include "ArkanoidByWered/GameModes/ABWGameModeBase.h"
#include "PaperSpriteComponent.h"

AABWBrick::AABWBrick()
{
	PrimaryActorTick.bCanEverTick = false;

	MainSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Main Sprite"));
	RootComponent = MainSpriteComp;
	MainSpriteComp->SetCollisionProfileName(TEXT("BlockAll"));
}

void AABWBrick::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());

	OnActorHit.AddDynamic(this, &AABWBrick::HandleOnHit);
}

void AABWBrick::HandleOnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(AABWBall::StaticClass()))
	{
		if (NumOfHits < BrokenBrickSprites.Num() && BrokenBrickSprites[NumOfHits])
		{
			MainSpriteComp->SetSprite(BrokenBrickSprites[NumOfHits]);
		}
		else
		{
			// todo add sound and maybe some animation
			Destroy();

			if (!GameMode)
			{
				UE_LOG(LogTemp, Warning, TEXT("AABWBrick::HandleOnHit|GameMode is null"));
				return;
			}

			GameMode->HandleBrickDestruction();
		}
		NumOfHits++;
	}
}
