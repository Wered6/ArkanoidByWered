// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWLevelSubsystem.h"
#include "ABWLevelData.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"
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
		UE_LOG(LogLevelSubsystem, Warning, TEXT("UABWLevelSubsystem::OpenCurrentLevel|CurrentLevelName is None"));
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
}

void UABWLevelSubsystem::OpenNextLevel()
{
	SetNextLevelName();

	if (NextLevelName.IsNone())
	{
		UE_LOG(LogLevelSubsystem, Warning, TEXT("UABWLevelSubsystem::OpenNextLevel|NextLevelName is None"));
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}

void UABWLevelSubsystem::SetCurrentLevelIndex()
{
	const FName CurrLevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));

	for (int i = 0; i < LevelsDataArray.Num(); i++)
	{
		const FName LevelName = LevelsDataArray[i]->GetLevelName();
		if (LevelName == CurrLevelName)
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
		UE_LOG(LogLevelSubsystem, Warning,
		       TEXT("UABWLevelSubsystem::CompleteCurrentLevel|CurrentLevelIndex out of bounds!"));
		return;
	}

	LevelsDataArray[CurrentLevelIndex]->SetIsLevelCompleted(true);
	UnlockNextLevel();
}

const TArray<UABWLevelData*>& UABWLevelSubsystem::GetLevelsDataArray() const
{
	return LevelsDataArray;
}

void UABWLevelSubsystem::InitializeLevels()
{
	Level1Data = UABWLevelData::CreateUABWLevelData(this, TEXT("Level1"), true);
	Level2Data = UABWLevelData::CreateUABWLevelData(this, TEXT("Level2"));
	Level3Data = UABWLevelData::CreateUABWLevelData(this, TEXT("Level3"));

	LevelsDataArray.Add(Level1Data);
	LevelsDataArray.Add(Level2Data);
	LevelsDataArray.Add(Level3Data);
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
		LevelsDataArray[NextLevelIndex]->SetIsLevelUnlocked(true);
	}
}

void UABWLevelSubsystem::SetCurrentLevelName()
{
	if (!LevelsDataArray.IsValidIndex(CurrentLevelIndex))
	{
		UE_LOG(LogLevelSubsystem, Warning,
		       TEXT("UABWLevelSubsystem::SetCurrentLevelName|CurrentLevelIndex out of bounds!"));
		return;
	}

	const UABWLevelData* CurrentLevel = LevelsDataArray[CurrentLevelIndex];
	CurrentLevelName = CurrentLevel->GetLevelName();
}

void UABWLevelSubsystem::SetNextLevelName()
{
	const int32 NextLevelIndex = CurrentLevelIndex + 1;

	if (NextLevelIndex < LevelsDataArray.Num())
	{
		const UABWLevelData* NextLevel = LevelsDataArray[NextLevelIndex];
		NextLevelName = NextLevel->GetLevelName();
	}
	else
	{
		NextLevelName = NAME_None;
	}
}
