// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameModeBase.h"
#include "ArkanoidByWered/Core/LevelSystem/ABWLevelSubsystem.h"
#include "ArkanoidByWered/GameInstance/ABWGameInstance.h"
#include "ArkanoidByWered/PlayerControllers/ABWPlayerController.h"
#include "ArkanoidByWered/GameplayElements/ABWBall.h"
#include "ArkanoidByWered/GameplayElements/ABWBrick.h"
#include "Kismet/GameplayStatics.h"

void AABWGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Init();
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

void AABWGameModeBase::Init()
{
	GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	LevelSubsystem = GameInstance->GetSubsystem<UABWLevelSubsystem>();
	PlayerController = Cast<AABWPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));
}

void AABWGameModeBase::StartGame()
{
	BallsNum = GetBallsCount();
	BricksNum = GetBricksCount();

	GameInstance->SetHasPlayerStartGame(true);
}

void AABWGameModeBase::LevelOver(const bool bWin) const
{
	PlayerController->SetPlayerEnabledState(false);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, bWin]()
	{
		HandleLevelOver(bWin);
	}, 1.5f, false);
}

void AABWGameModeBase::HandleLevelOver(const bool bWin) const
{
	if (bWin)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
		GameInstance->SetHasPlayerWonLevel(true);

		LevelSubsystem->SetCurrentLevelIndex();
		LevelSubsystem->CompleteCurrentLevel();
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
		GameInstance->SetHasPlayerWonLevel(false);
	}
}

int32 AABWGameModeBase::GetBallsCount() const
{
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsOfClass(this, AABWBall::StaticClass(), Balls);
	return Balls.Num();
}

int32 AABWGameModeBase::GetBricksCount() const
{
	TArray<AActor*> Bricks;
	UGameplayStatics::GetAllActorsOfClass(this, AABWBrick::StaticClass(), Bricks);
	return Bricks.Num();
}
