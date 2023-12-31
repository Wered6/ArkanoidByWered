// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABWPlayerController.generated.h"

class AABWGameModeBase;
class UABWPlayerStats;
class AABWPaddle;
class AABWBall;
class AABWHUD;

UCLASS()
class ARKANOIDBYWERED_API AABWPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AABWPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void SetPlayerEnabledState(const bool bPlayerEnabled);

	void IncrementLife();
	void DecrementLife();
	int32 GetLifes() const;

private:
	void InitializeGameLogic();
	void InitializeGameplayElements();
	void InitializeHUD();

	void MovePaddle(const float Value);

	void SpawnBall();
	void LaunchBall();
	void UpdateIdleBallPosition() const;

	UPROPERTY()
	AABWHUD* HUD{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<AABWBall> BallClass;
	UPROPERTY()
	AABWBall* SpawnedBall{nullptr};

	UPROPERTY()
	AABWPaddle* Paddle{nullptr};

	UPROPERTY()
	UABWPlayerStats* PlayerStats{nullptr};

	UPROPERTY()
	AABWGameModeBase* GameMode{nullptr};
};
