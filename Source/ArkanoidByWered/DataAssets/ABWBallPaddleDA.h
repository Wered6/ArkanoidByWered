// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABWBallPaddleDA.generated.h"

class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UABWBallPaddleDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Balls")
	TArray<UPaperSprite*> BallsSprites;

	UPROPERTY(EditAnywhere, Category="Paddles")
	TArray<UPaperSprite*> PaddlesSprites;
};
