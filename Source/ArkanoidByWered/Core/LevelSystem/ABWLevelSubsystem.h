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

	FName GetCurrentLevelName() const;
	void CompleteCurrentLevel();

private:
	void InitializeLevels();
	void DeinitializeLevels();

	bool bInitialized{false};

	int32 CurrentLevelIndex{0};

	TArray<FLevelData> LevelsData;
};
