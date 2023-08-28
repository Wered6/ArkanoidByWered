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
	void BallWasDestroyed(AActor* DestroyedBall);
	void BrickWasDestroyed(AActor* DestroyedBrick);

	int32 GetBallsCount() const;
	int32 GetBricksCount() const;

protected:
	virtual void BeginPlay() override;

	void StartGame();
	void LevelOver();
	void GameOver();

private:
	UPROPERTY()
	APaddle* Paddle{nullptr};
	UPROPERTY()
	AABWPlayerController* ABWPlayerController{nullptr};
	UPROPERTY()
	ABall* SpawnedBall{nullptr};

	int32 BallsCount{0};
	int32 BricksCount{0};
};
