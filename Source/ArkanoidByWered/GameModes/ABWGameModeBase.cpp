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
	check(CheckNullPointers());
	StartGame();
}

void AABWGameModeBase::BallWasDestroyed()
{
	BallsNum--;
	if (BallsNum <= 0)
	{
		PlayerController->SubLife();

		if (PlayerController->GetLife() <= 0)
		{
			FTimerHandle TimerHandle;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				LevelOver(false);
			}, 1.5f, false);
		}
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

bool AABWGameModeBase::CheckNullPointers() const
{
	if (!GameInstance)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::CheckNullPointers|GameInstance is null"));
		return false;
	}
	if (!LevelSubsystem)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::CheckNullPointers|LevelSubsystem is null"));
		return false;
	}
	if (!PlayerController)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::CheckNullPointers|PlayerController is null"));
		return false;
	}
	return true;
}

void AABWGameModeBase::LevelOver(const bool bWin) const
{
	PlayerController->SetPlayerEnabledState(false);
	GameInstance->SetHasPlayerWonLevel(bWin);

	if (bWin)
	{
		LevelSubsystem->SetCurrentLevelIndex();
		LevelSubsystem->CompleteCurrentLevel();
	}

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
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
