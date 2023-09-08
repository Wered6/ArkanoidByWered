// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWSaveGame.h"

#include "ArkanoidByWered/DataAssets/ABWDefaultBallPaddleDA.h"

UABWSaveGame::UABWSaveGame()
{
	static ConstructorHelpers::FObjectFinder<UABWDefaultBallPaddleDA> DefaultBallPaddleDAFinder(
		TEXT(
			"/Script/ArkanoidByWered.DefaultBallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/DefaultBallPaddleDA.DefaultBallPaddleDA'"));
	if (!DefaultBallPaddleDAFinder.Succeeded())
	{
		UE_LOG(LogAssetData, Warning, TEXT("UABWSaveGame::UABWSaveGame|DefaultBallPaddleDAFinder didnt succeeded"));
		return;
	}
	DefaultBallPaddleDA = DefaultBallPaddleDAFinder.Object;
	BallSprite = DefaultBallPaddleDA->DefaultBallSprite;
	PaddleSprite = DefaultBallPaddleDA->DefaultPaddleSprite;
}

void UABWSaveGame::SetBallSprite(UPaperSprite* SelectedBallSprite)
{
	BallSprite = SelectedBallSprite;
}

void UABWSaveGame::SetPaddleSprite(UPaperSprite* SelectedPaddleSprite)
{
	PaddleSprite = SelectedPaddleSprite;
}

UPaperSprite* UABWSaveGame::GetBallSprite() const
{
	return BallSprite;
}

UPaperSprite* UABWSaveGame::GetPaddleSprite() const
{
	return PaddleSprite;
}
