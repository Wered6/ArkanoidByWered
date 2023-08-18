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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
