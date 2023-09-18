// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWLevelData.h"

UABWLevelData* UABWLevelData::CreateUABWLevelData(UObject* WorldContextObject,
                                                  const FName LevelName,
                                                  const bool bIsLevelUnlocked,
                                                  const bool bIsLevelCompleted)
{
	UABWLevelData* LevelData = NewObject<UABWLevelData>(WorldContextObject);

	if (LevelData)
	{
		LevelData->LevelName = LevelName;
		LevelData->bIsLevelUnlocked = bIsLevelUnlocked;
		LevelData->bIsLevelCompleted = bIsLevelCompleted;
	}

	return LevelData;
}

FName UABWLevelData::GetLevelName() const
{
	return LevelName;
}

bool UABWLevelData::GetIsLevelUnlocked() const
{
	return bIsLevelUnlocked;
}

void UABWLevelData::SetIsLevelUnlocked(const bool bLevelUnlocked)
{
	bIsLevelUnlocked = bLevelUnlocked;
}

bool UABWLevelData::GetIsLevelCompleted() const
{
	return bIsLevelCompleted;
}

void UABWLevelData::SetIsLevelCompleted(const bool bLevelCompleted)
{
	bIsLevelCompleted = bLevelCompleted;
}
