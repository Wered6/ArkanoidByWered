// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ABWGameInstance.generated.h"

class UABWLevelSubsystem;

UCLASS()
class ARKANOIDBYWERED_API UABWGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	void InitializeGameLogic();

	bool GetHasPlayerWonLevel() const;
	void SetHasPlayerWonLevel(const bool bPlayerWonLevel);

	bool GetHasPlayerStartGame() const;
	void SetHasPlayerStartGame(const bool bPlayerStartGame);

	bool GetHasCompletedAllLevels() const;

	bool GetIsCurrentLevelLast() const;

private:
	bool bHasPlayerWonLevel{false};
	bool bHasPlayerStartGame{false};
	bool bHasCompletedAllLevels{false};
	bool bIsCurrentLevelLast{false};

	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem;
};
