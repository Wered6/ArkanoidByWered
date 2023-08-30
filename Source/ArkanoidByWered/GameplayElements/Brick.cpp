// Copyright (c) 2023 Wered. All rights reserved.


#include "Brick.h"
#include "Ball.h"
#include "ArkanoidByWered/GameModes/ABWGameModeBase.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABrick::ABrick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MainSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Main Sprite"));
	RootComponent = MainSpriteComp;
	MainSpriteComp->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());
	
	OnActorHit.AddDynamic(this, &ABrick::HandleOnHit);
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrick::HandleOnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(ABall::StaticClass()))
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