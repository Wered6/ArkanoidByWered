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
	UPaperSprite* GetPaddleSprite() const;
	UPaperSprite* GetBallSprite() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Sprites|Paddle")
	UPaperSprite* DefaultPaddleSprite;

	UPROPERTY(EditDefaultsOnly, Category="Sprites|Ball")
	UPaperSprite* DefaultBallSprite;
};
