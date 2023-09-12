// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABWPlayerController.generated.h"

class AABWGameModeBase;
class AABWPaddle;
class AABWBall;
class UWidgetAnimation;
class UABWHUDWidget;

UCLASS()
class ARKANOIDBYWERED_API AABWPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AABWPlayerController();

	void AddLife();
	void SubLife();
	int32 GetLife() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void SetPlayerEnabledState(const bool bPlayerEnabled);

private:
	void SetHUD();

	void SetPaddle();
	void MovePaddle(const float Value);

	void SpawnBall();
	void LaunchBall();
	void UpdateIdleBallPosition() const;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UABWHUDWidget> HUDWidgetClass;
	UPROPERTY()
	UABWHUDWidget* HUD{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<AABWBall> BallClass;
	UPROPERTY()
	AABWBall* SpawnedBall{nullptr};

	UPROPERTY()
	AABWPaddle* Paddle{nullptr};

	int32 Lifes{3};

	UPROPERTY()
	AABWGameModeBase* GameMode{nullptr};
};