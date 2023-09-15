// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ABWLevelSubsystem.generated.h"

USTRUCT()
struct FLevelData
{
	GENERATED_BODY()

	FLevelData()
	{
	}

	FLevelData(const FName& LevelName)
		: LevelName(LevelName)
	{
	}

	UPROPERTY()
	FName LevelName;

	UPROPERTY()
	bool bIsLevelUnlocked{false};

	UPROPERTY()
	bool bIsLevelCompleted{false};
};

UCLASS()
class ARKANOIDBYWERED_API UABWLevelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End

	UFUNCTION(BlueprintCallable, Category="Levels")
	void OpenCurrentLevel();
	UFUNCTION(BlueprintCallable, Category="Levels")
	void OpenNextLevel();

	void SetCurrentLevelIndex();
	int32 GetCurrentLevelIndex() const;

	void CompleteCurrentLevel();

	const TArray<FLevelData*>& GetLevelsDataArray() const;

private:
	void InitializeLevels();
	void DeinitializeLevels();

	void UnlockNextLevel();

	void SetCurrentLevelName();
	void SetNextLevelName();

	bool bInitialized{false};

	int32 CurrentLevelIndex{0};

	FName CurrentLevelName{NAME_None};
	FName NextLevelName{NAME_None};

	FLevelData Level1Data{TEXT("Level1")};
	FLevelData Level2Data{TEXT("Level2")};
	FLevelData Level3Data{TEXT("Level3")};

	TArray<FLevelData*> LevelsDataArray;
};
