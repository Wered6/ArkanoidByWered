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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void SetPlayerEnabledState(const bool bPlayerEnabled);

	void AddLife();
	void SubLife();
	int32 GetLife() const;

private:
	void Init();
	void SetHUD();
	void SetPaddle();
	void SetGameMode();
	bool CheckNullPointers() const;

	void StartGame();

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

	const int32 MaxLifes{3};
	const int32 MinLifes{0};
	int32 Lifes;

	UPROPERTY()
	AABWGameModeBase* GameMode{nullptr};
};
