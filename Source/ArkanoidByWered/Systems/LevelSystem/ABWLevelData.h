// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ABWLevelData.generated.h"

UCLASS()
class ARKANOIDBYWERED_API UABWLevelData : public UObject
{
	GENERATED_BODY()

public:
	static UABWLevelData* CreateUABWLevelData(UObject* WorldContextObject,
	                                          const FName LevelName,
	                                          const bool bIsLevelUnlocked = false,
	                                          const bool bIsLevelCompleted = false);

	FName GetLevelName() const;

	bool GetIsLevelUnlocked() const;
	void SetIsLevelUnlocked(const bool bLevelUnlocked);

	bool GetIsLevelCompleted() const;
	void SetIsLevelCompleted(const bool bLevelCompleted);

private:
	FName LevelName;
	bool bIsLevelUnlocked{false};
	bool bIsLevelCompleted{false};
};
