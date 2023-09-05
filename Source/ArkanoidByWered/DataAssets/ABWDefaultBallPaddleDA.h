// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABWDefaultBallPaddleDA.generated.h"

class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UABWDefaultBallPaddleDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Defaults")
	UPaperSprite* DefaultPaddleSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Defaults")
	UPaperSprite* DefaultBallSprite;
};