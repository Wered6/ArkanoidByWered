// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABWGameModeBase.generated.h"

class AABWPlayerController;
class APaddle;
class ABall;

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
	void StartGame();
	void LevelOver(const bool bWin);
	
	int32 GetBallsCount() const;
	int32 GetBricksCount() const;

	UPROPERTY()
	APaddle* Paddle{nullptr};
	UPROPERTY()
	AABWPlayerController* PlayerController{nullptr};

	int32 BallsNum{0};
	int32 BricksNum{0};
};
