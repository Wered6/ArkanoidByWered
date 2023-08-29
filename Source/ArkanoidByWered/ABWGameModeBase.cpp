// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameModeBase.h"
#include "GameInstance/ABWGameInstance.h"
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

void AABWGameModeBase::StartGame()
{
	GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	PlayerController = Cast<AABWPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));
	Paddle = Cast<APaddle>(UGameplayStatics::GetPlayerPawn(this, 0));
	BallsNum = GetBallsCount();
	BricksNum = GetBricksCount();
}

void AABWGameModeBase::LevelOver(const bool bWin) const
{
	PlayerController->SetPlayerEnabledState(false);
	if (bWin)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
		GameInstance->SetHasPlayerLost(false);
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(),TEXT("MainMenu"));
		GameInstance->SetHasPlayerLost(true);
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
