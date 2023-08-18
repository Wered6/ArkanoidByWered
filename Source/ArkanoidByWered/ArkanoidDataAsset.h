// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ArkanoidDataAsset.generated.h"

class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UArkanoidDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Balls")
	TArray<UPaperSprite*> BallsSprites;

	UPROPERTY(EditAnywhere, Category="Paddles")
	TArray<UPaperSprite*> PaddlesSprites;
};
