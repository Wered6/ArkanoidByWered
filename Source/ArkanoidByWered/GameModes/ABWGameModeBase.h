// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABWGameModeBase.generated.h"

class AABWPlayerController;
class UABWLevelSubsystem;
class UABWGameInstance;
class AABWPaddle;

UCLASS()
class ARKANOIDBYWERED_API AABWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void BallWasDestroyed();
	void BrickWasDestroyed();

protected:
	virtual void BeginPlay() override;

private:
	void Init();
	void StartGame();
	void LevelOver(const bool bWin) const;

	int32 GetBallsCount() const;
	int32 GetBricksCount() const;

	int32 BallsNum{0};
	int32 BricksNum{0};

	UPROPERTY()
	UABWGameInstance* GameInstance{nullptr};
	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem{nullptr};
	UPROPERTY()
	AABWPlayerController* PlayerController{nullptr};
};
