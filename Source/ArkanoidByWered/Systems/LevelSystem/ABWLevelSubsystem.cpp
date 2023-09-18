// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWLevelSubsystem.h"
#include "ABWLevelData.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"
#include "ArkanoidByWered/Utilities/JSON/JsonUtility.h"
#include "Kismet/GameplayStatics.h"

void UABWLevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;

	InitializeLevelsDataArray();
}

void UABWLevelSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
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

TArray<UABWLevelData*> UABWLevelSubsystem::GetLevelsDataArray() const
{
	return LevelsDataArray;
}

void UABWLevelSubsystem::InitializeLevelsDataArray()
{
	FString JsonFilePath;
	if (GConfig->GetString(TEXT("GameConfig"), TEXT("LevelsJsonPath"), JsonFilePath, GEngineIni))
	{
		JsonFilePath = FPaths::ProjectDir() + JsonFilePath;
		TArray<UABWLevelData*> NewLevelsDataArray;

		if (FJsonUtility::LoadLevelDataFromJson(this, JsonFilePath, NewLevelsDataArray))
		{
			LevelsDataArray = NewLevelsDataArray;
		}
		else
		{
			UE_LOG(LogLevelSubsystem, Error,
			       TEXT(
				       "UABWLevelSubsystem::InitializeLevelsDataArray|Initialization failed: Could not load level data from JSON."
			       ));
		}
	}
	else
	{
		UE_LOG(LogLevelSubsystem, Error,
		       TEXT("UABWLevelSubsystem::InitializeLevelsDataArray|LevelsJsonPath not found in INI file"));
	}
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
