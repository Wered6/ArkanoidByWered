// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWBrick.h"
#include "ArkanoidByWered/GameplayElements/Ball/ABWBall.h"
#include "ArkanoidByWered/GameModes/Gameplay/ABWGameModeBase.h"
#include "PaperSpriteComponent.h"

AABWBrick::AABWBrick()
{
	PrimaryActorTick.bCanEverTick = false;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = SpriteComp;
	SpriteComp->SetCollisionProfileName(TEXT("BlockAll"));
}

void AABWBrick::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());

	OnActorHit.AddDynamic(this, &AABWBrick::HandleOnHit);
}

void AABWBrick::HandleOnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GameMode)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWBrick::HandleOnHit|GameMode is nullptr"));
		return;
	}
	if (!SpriteComp)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWBrick::HandleOnHit|SpriteCOmp is nullptr"));
		return;
	}
	
	if (OtherActor && OtherActor->IsA(AABWBall::StaticClass()))
	{
		if (NumOfHits < BrokenBrickSprites.Num() && BrokenBrickSprites[NumOfHits])
		{
			SpriteComp->SetSprite(BrokenBrickSprites[NumOfHits]);
		}
		else
		{
			Destroy();
			GameMode->HandleBrickDestruction();
		}
		NumOfHits++;
	}
}
