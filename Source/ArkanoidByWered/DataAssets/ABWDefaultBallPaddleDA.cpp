// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWDefaultBallPaddleDA.h"

UPaperSprite* UABWDefaultBallPaddleDA::GetPaddleSprite() const
{
	if (!DefaultPaddleSprite)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UABWDefaultBallPaddleDA::GetPaddleSprite|DefaultPaddleSprite is nullptr"));
	}

	return DefaultPaddleSprite;
}

UPaperSprite* UABWDefaultBallPaddleDA::GetBallSprite() const
{
	if (!DefaultBallSprite)
	{
		UE_LOG(LogAssetData, Warning, TEXT("UABWDefaultBallPaddleDA::GetBallSprite|DefaultBallSprite is nullptr"));
	}

	return DefaultBallSprite;
}
