// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameInstance.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelData.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelSubsystem.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"


void UABWGameInstance::Init()
{
	Super::Init();

	InitializeGameLogic();
}

void UABWGameInstance::InitializeGameLogic()
{
	LevelSubsystem = GetSubsystem<UABWLevelSubsystem>();
}

bool UABWGameInstance::GetHasPlayerWonLevel() const
{
	return bHasPlayerWonLevel;
}

void UABWGameInstance::SetHasPlayerWonLevel(const bool bPlayerWonLevel)
{
	bHasPlayerWonLevel = bPlayerWonLevel;
}

bool UABWGameInstance::GetHasPlayerStartGame() const
{
	return bHasPlayerStartGame;
}

void UABWGameInstance::SetHasPlayerStartGame(const bool bPlayerStartGame)
{
	bHasPlayerStartGame = bPlayerStartGame;
}

bool UABWGameInstance::GetHasCompletedAllLevels() const
{
	if (!LevelSubsystem)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UABWGameInstance::GetHasCompletedAllLevels|LevelSubsystem is nullptr"));
		return false;
	}

	bool bAllLevelsCompleted{false};
	TArray<UABWLevelData*> LevelsDataArray = LevelSubsystem->GetLevelsDataArray();

	for (const auto& LevelData : LevelsDataArray)
	{
		bAllLevelsCompleted = LevelData->GetIsLevelCompleted();
		if (!bAllLevelsCompleted)
		{
			break;
		}
	}
	return bAllLevelsCompleted;
}

bool UABWGameInstance::GetIsCurrentLevelLast() const
{
	if (!LevelSubsystem)
	{
		UE_LOG(LogGameInstance, Warning, TEXT("UABWGameInstance::GetIsCurrentLevelLast|LevelSubsystem is nullptr"));
		return false;
	}

	const int32 CurrentLevelIndex = LevelSubsystem->GetCurrentLevelIndex();
	const TArray<UABWLevelData*> LevelsDataArray = LevelSubsystem->GetLevelsDataArray();

	return CurrentLevelIndex == LevelsDataArray.Num() - 1;
}
