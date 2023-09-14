// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWCustomizationSaveGame.h"
#include "ArkanoidByWered/DataAssets/ABWDefaultBallPaddleDA.h"

UABWCustomizationSaveGame::UABWCustomizationSaveGame()
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

void UABWCustomizationSaveGame::SetBallSprite(UPaperSprite* SelectedBallSprite)
{
	BallSprite = SelectedBallSprite;
}

void UABWCustomizationSaveGame::SetPaddleSprite(UPaperSprite* SelectedPaddleSprite)
{
	PaddleSprite = SelectedPaddleSprite;
}

UPaperSprite* UABWCustomizationSaveGame::GetBallSprite() const
{
	return BallSprite;
}

UPaperSprite* UABWCustomizationSaveGame::GetPaddleSprite() const
{
	return PaddleSprite;
}
