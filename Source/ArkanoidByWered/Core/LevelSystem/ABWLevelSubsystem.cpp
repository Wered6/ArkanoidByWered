// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWLevelSubsystem.h"

void UABWLevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;

	InitializeLevels();
}

void UABWLevelSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;

	DeinitializeLevels();
}

FName UABWLevelSubsystem::GetCurrentLevelName() const
{
	return LevelsData[CurrentLevelIndex].LevelName;
}

void UABWLevelSubsystem::CompleteCurrentLevel()
{
	LevelsData[CurrentLevelIndex].bIsLevelCompleted = true;
	CurrentLevelIndex++;
	if (LevelsData.IsValidIndex(CurrentLevelIndex))
	{
		LevelsData[CurrentLevelIndex].bIsLevelUnlocked = true;
	}
	else
	{
		CurrentLevelIndex = -1;
	}
}

void UABWLevelSubsystem::InitializeLevels()
{
	LevelsData.Add(FLevelData(TEXT("Level1")));
	LevelsData.Add(FLevelData(TEXT("Level2")));
	LevelsData.Add(FLevelData(TEXT("Level3")));

	LevelsData[0].bIsLevelUnlocked = true;
}

void UABWLevelSubsystem::DeinitializeLevels()
{
	LevelsData.Empty();
}
