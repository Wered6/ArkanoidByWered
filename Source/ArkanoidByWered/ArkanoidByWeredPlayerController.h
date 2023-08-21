// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArkanoidByWeredPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOIDBYWERED_API AArkanoidByWeredPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AddLive();
	void SubLive();
	int32 GetLives() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int32 Lives{3};
};
