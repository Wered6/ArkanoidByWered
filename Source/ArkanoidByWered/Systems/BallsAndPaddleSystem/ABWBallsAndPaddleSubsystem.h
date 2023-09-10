// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ABWBallsAndPaddleSubsystem.generated.h"

class AABWPaddle;
class AABWBall;

UCLASS()
class ARKANOIDBYWERED_API UABWBallsAndPaddleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End

private:
	void AddBall(AABWBall* Ball);
	void RemoveBall(AABWBall* Ball);
	
	bool bInitialized{false};
	
	UPROPERTY()
	TArray<AABWBall*> Balls;
	UPROPERTY()
	AABWPaddle* Paddle{nullptr};
};
