// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWBallPaddleDA.h"

UPaperSprite* UABWBallPaddleDA::GetPaddleSpriteAtIndex(const int32 PaddleIndex) const
{
	if (!PaddlesSprites.IsValidIndex(PaddleIndex))
	{
		UE_LOG(LogAssetData, Warning, TEXT("UABWBallPaddleDA::GetPaddleSpriteAtIndex|PaddleIndex is out of bounds!"));
		return nullptr;
	}

	return PaddlesSprites[PaddleIndex];
}

UPaperSprite* UABWBallPaddleDA::GetBallSpriteAtIndex(const int32 BallIndex) const
{
	if (!BallsSprites.IsValidIndex(BallIndex))
	{
		UE_LOG(LogAssetData, Warning, TEXT("UABWBallPaddleDA::GetBallSpriteAtIndex|BallIndex is out of bounds!"));
		return nullptr;
	}

	return BallsSprites[BallIndex];
}

int32 UABWBallPaddleDA::GetPaddlesSpritesNum() const
{
	return PaddlesSprites.Num();
}

int32 UABWBallPaddleDA::GetBallsSpritesNum() const
{
	return BallsSprites.Num();
}
