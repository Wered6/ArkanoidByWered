// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWLevelSubsystem.h"
#include "Kismet/GameplayStatics.h"

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

void UABWLevelSubsystem::OpenCurrentLevel()
{
	SetCurrentLevelName();
	if (CurrentLevelName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWLevelSubsystem::OpenCurrentLevel|CurrentLevelName is None"));
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
}

void UABWLevelSubsystem::OpenNextLevel()
{
	SetNextLevelName();
	if (NextLevelName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWLevelSubsystem::OpenNextLevel|NextLevelName is None"));
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}

void UABWLevelSubsystem::SetCurrentLevelIndex()
{
	const FName LevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));

	for (int i = 0; i < LevelsDataArray.Num(); i++)
	{
		if (LevelsDataArray[i]->LevelName == LevelName)
		{
			CurrentLevelIndex = i;
			break;
		}
	}
}

int32 UABWLevelSubsystem::GetCurrentLevelIndex() const
{
	return CurrentLevelIndex;
}

void UABWLevelSubsystem::CompleteCurrentLevel()
{
	if (!LevelsDataArray.IsValidIndex(CurrentLevelIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWLevelSubsystem::CompleteCurrentLevel|CurrentLevelIndex out of bounds!"));
		return;
	}

	LevelsDataArray[CurrentLevelIndex]->bIsLevelCompleted = true;
	UnlockNextLevel();
}

TArray<FLevelData*> UABWLevelSubsystem::GetLevelsDataArray()
{
	return LevelsDataArray;
}

void UABWLevelSubsystem::InitializeLevels()
{
	LevelsDataArray.Add(&Level1Data);
	LevelsDataArray.Add(&Level2Data);
	LevelsDataArray.Add(&Level3Data);

	LevelsDataArray[0]->bIsLevelUnlocked = true;
}

void UABWLevelSubsystem::DeinitializeLevels()
{
	LevelsDataArray.Empty();
}

void UABWLevelSubsystem::UnlockNextLevel()
{
	const int32 NextLevelIndex = CurrentLevelIndex + 1;
	if (NextLevelIndex < LevelsDataArray.Num())
	{
		LevelsDataArray[NextLevelIndex]->bIsLevelUnlocked = true;
	}
}

void UABWLevelSubsystem::SetCurrentLevelName()
{
	if (!LevelsDataArray.IsValidIndex(CurrentLevelIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWLevelSubsystem::SetCurrentLevelName|CurrentLevelIndex out of bounds!"));
		return;
	}

	const FLevelData* CurrentLevel = LevelsDataArray[CurrentLevelIndex];
	CurrentLevelName = CurrentLevel->LevelName;
}

void UABWLevelSubsystem::SetNextLevelName()
{
	const int32 NextLevelIndex = CurrentLevelIndex + 1;

	if (NextLevelIndex < LevelsDataArray.Num())
	{
		const FLevelData* CurrentLevel = LevelsDataArray[NextLevelIndex];
		NextLevelName = CurrentLevel->LevelName;
	}
	else
	{
		NextLevelName = NAME_None;
	}
}
