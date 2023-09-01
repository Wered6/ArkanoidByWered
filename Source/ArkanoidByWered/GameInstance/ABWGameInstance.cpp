// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameInstance.h"

UABWGameInstance::UABWGameInstance()
{
	FLevelInfo Level1Info;
	Level1Info.LevelName = TEXT("Level1");
	Level1Info.bIsLevelUnlocked = true;
	Level1Info.bIsLevelCompleted = false;

	FLevelInfo Level2Info;
	Level2Info.LevelName = TEXT("Level2");
	Level2Info.bIsLevelUnlocked = false;
	Level2Info.bIsLevelCompleted = false;

	FLevelInfo Level3Info;
	Level3Info.LevelName = TEXT("Level3");
	Level3Info.bIsLevelUnlocked = false;
	Level3Info.bIsLevelCompleted = false;

	LevelsInfo.Add(Level1Info);
	LevelsInfo.Add(Level2Info);
	LevelsInfo.Add(Level3Info);
}

bool UABWGameInstance::GetHasPlayerLost() const
{
	return bHasPlayerLost;
}

void UABWGameInstance::SetHasPlayerLost(const bool bPlayerHasLost)
{
	bHasPlayerLost = bPlayerHasLost;
}

FString UABWGameInstance::GetLevelNameByIndex(const int32 LevelIndex) const
{
	return LevelsInfo[LevelIndex].LevelName;
}

bool UABWGameInstance::GetIsLevelUnlockedByIndex(const int32 LevelIndex) const
{
	return LevelsInfo[LevelIndex].bIsLevelUnlocked;
}

bool UABWGameInstance::GetIsLevelCompletedByIndex(const int32 LevelIndex) const
{
	return LevelsInfo[LevelIndex].bIsLevelCompleted;
}

void UABWGameInstance::UnlockLevelByIndex(const int32 LevelIndex)
{
	LevelsInfo[LevelIndex].bIsLevelUnlocked = true;
}

void UABWGameInstance::CompleteLevelByIndex(const int32 LevelIndex)
{
	LevelsInfo[LevelIndex].bIsLevelCompleted = true;
}
