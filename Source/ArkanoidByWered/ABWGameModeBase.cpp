// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameModeBase.h"
#include "ABWPlayerController.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Kismet/GameplayStatics.h"

void AABWGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	StartGame();
}

void AABWGameModeBase::StartGame()
{
	BallsNum = GetBallsCount();
	BricksNum = GetBricksCount();
	Paddle = Cast<APaddle>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AABWPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));
}

void AABWGameModeBase::LevelOver(const bool bWin)
{
	PlayerController->SetPlayerEnabledState(false);

	if (bWin)
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Won"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Lost"));
	}
	// todo add UI with buttons "Next level", "Menu"
}

void AABWGameModeBase::BallWasDestroyed()
{
	BallsNum--;
	if (BallsNum <= 0)
	{
		PlayerController->SubLife();
	}
	if (PlayerController->GetLife() <= 0)
	{
		LevelOver(false);
	}
}

void AABWGameModeBase::BrickWasDestroyed()
{
	BricksNum--;
	if (BricksNum <= 0)
	{
		LevelOver(true);
	}
}

int32 AABWGameModeBase::GetBallsCount() const
{
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsOfClass(this, ABall::StaticClass(), Balls);
	return Balls.Num();
}

int32 AABWGameModeBase::GetBricksCount() const
{
	TArray<AActor*> Bricks;
	UGameplayStatics::GetAllActorsOfClass(this, ABrick::StaticClass(), Bricks);
	return Bricks.Num();
}
