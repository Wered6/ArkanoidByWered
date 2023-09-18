// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ABWLevelSubsystem.generated.h"

class UABWLevelData;

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

	const TArray<UABWLevelData*>& GetLevelsDataArray() const;

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

	UPROPERTY()
	UABWLevelData* Level1Data{nullptr};
	UPROPERTY()
	UABWLevelData* Level2Data{nullptr};
	UPROPERTY()
	UABWLevelData* Level3Data{nullptr};

	TArray<UABWLevelData*> LevelsDataArray;
};
