// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ABWGameInstance.generated.h"

USTRUCT()
struct FLevelInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString LevelName;

	UPROPERTY()
	bool bIsLevelUnlocked;

	UPROPERTY()
	bool bIsLevelCompleted;
};

UCLASS()
class ARKANOIDBYWERED_API UABWGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UABWGameInstance();

	bool GetHasPlayerLost() const;
	void SetHasPlayerLost(const bool bPlayerHasLost);

	FString GetLevelNameByIndex(const int32 LevelIndex) const;
	bool GetIsLevelUnlockedByIndex(const int32 LevelIndex) const;
	bool GetIsLevelCompletedByIndex(const int32 LevelIndex) const;

	void UnlockLevelByIndex(const int32 LevelIndex);
	void CompleteLevelByIndex(const int32 LevelIndex);

private:
	bool bHasPlayerLost{false};

	TArray<FLevelInfo> LevelsInfo;
};
