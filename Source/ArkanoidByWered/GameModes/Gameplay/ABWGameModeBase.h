// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABWGameModeBase.generated.h"

class AABWPlayerController;
class UABWLevelSubsystem;
class UABWGameInstance;
class AABWBall;

UCLASS()
class ARKANOIDBYWERED_API AABWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Ball and Brick destruction handlers
	void HandleBallDestruction(AABWBall* Ball);
	void HandleBrickDestruction();

	// Ball pool methods
	AABWBall* GetBall();
	void ReturnBall(AABWBall* Ball);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	// Initialization methods
	void InitializeGameLogic();
	void InitializeBallsPool(const int32 NumberOfBalls);

	// Level over logic
	void LevelOver(const bool bWin);

	// Counting game elements
	int32 GetBricksCount() const;

	// Timers
	FTimerHandle LevelOverTimerHandle;

	// Gammeplay elements
	UPROPERTY(EditDefaultsOnly, Category="Gameplay Elements|Balls")
	TSubclassOf<AABWBall> BallClass;

	// Ball pools
	UPROPERTY()
	TArray<AABWBall*> InactiveBalls;
	UPROPERTY()
	TArray<AABWBall*> ActiveBalls;

	// Game variables
	int32 NumberOfBricks{0};

	// Game sub-systems and controllers
	UPROPERTY()
	UABWGameInstance* GameInstance{nullptr};
	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem{nullptr};
	UPROPERTY()
	AABWPlayerController* PlayerController{nullptr};
};
