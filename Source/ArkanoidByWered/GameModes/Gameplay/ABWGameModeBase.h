// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABWGameModeBase.generated.h"

class AABWBall;
class AABWPlayerController;
class UABWLevelSubsystem;
class UABWGameInstance;
class AABWPaddle;

UCLASS()
class ARKANOIDBYWERED_API AABWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void HandleBallDestruction(AABWBall* Ball);
	void HandleBrickDestruction();

	AABWBall* GetBall();
	void ReturnBall(AABWBall* Ball);

protected:
	virtual void BeginPlay() override;

private:
	void Init();
	void StartGame();
	bool CheckNullPointers() const;

	void LevelOver(const bool bWin) const;

	int32 GetBallsCount() const;
	int32 GetBricksCount() const;

	void InitializeBallsPool(const int32 NumberOfBalls);

	UPROPERTY(EditDefaultsOnly, Category="Gameplay Elements")
	TSubclassOf<AABWBall> BallClass;

	UPROPERTY()
	TArray<AABWBall*> InactiveBalls;
	UPROPERTY()
	TArray<AABWBall*> ActiveBalls;

	int32 NumberOfBricks{0};

	UPROPERTY()
	UABWGameInstance* GameInstance{nullptr};
	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem{nullptr};
	UPROPERTY()
	AABWPlayerController* PlayerController{nullptr};
};
