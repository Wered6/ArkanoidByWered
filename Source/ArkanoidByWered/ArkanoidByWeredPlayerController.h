// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArkanoidByWeredPlayerController.generated.h"

class APaddle;
class ABall;
class UWidgetAnimation;
class UHUDWidget;

UCLASS()
class ARKANOIDBYWERED_API AArkanoidByWeredPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AArkanoidByWeredPlayerController();

	void AddLife();
	void SubLife();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

private:
	void SetPaddle();
	void MovePaddle(const float Value);

	void SpawnBall();
	void LaunchBall();
	void UpdateIdleBallPosition() const;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UHUDWidget> HUDWidgetClass;
	UPROPERTY()
	UHUDWidget* HUD{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<ABall> BallClass;
	UPROPERTY()
	ABall* SpawnedBall{nullptr};

	UPROPERTY()
	APaddle* Paddle{nullptr};

	int32 Lifes{3};
};
