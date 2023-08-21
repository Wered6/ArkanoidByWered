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
	
	void AddLive();
	void SubLive();

	void SpawnBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void SetPaddle();
	
	int32 Lives{3};

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UHUDWidget> HUDWidgetClass;
	UPROPERTY()
	UHUDWidget* HUD;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<ABall> BallClass;
	UPROPERTY()
	ABall* SpawnedBall;
	
	UPROPERTY()
	APaddle* Paddle;
};
