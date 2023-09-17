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
	UPaperSprite* GetPaddleSpriteAtIndex(const int32 PaddleIndex) const;
	UPaperSprite* GetBallSpriteAtIndex(const int32 BallIndex) const;

	int32 GetPaddlesSpritesNum() const;
	int32 GetBallsSpritesNum() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="Sprites|Balls")
	TArray<UPaperSprite*> BallsSprites;

	UPROPERTY(EditDefaultsOnly, Category="Sprites|Paddles")
	TArray<UPaperSprite*> PaddlesSprites;
};
