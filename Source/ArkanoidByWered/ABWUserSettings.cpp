// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWUserSettings.h"
#include "DefaultBallPaddleDA.h"

UABWUserSettings::UABWUserSettings()
{
	static ConstructorHelpers::FObjectFinder<UDefaultBallPaddleDA> DefaultSettingsAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.DefaultBallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/DefaultBallPaddleDA.DefaultBallPaddleDA'"));
	if (DefaultSettingsAssetFinder.Succeeded())
	{
		DefaultSettingsAsset = DefaultSettingsAssetFinder.Object;
		SelectedBall = DefaultSettingsAsset->DefaultBallSprite;
		SelectedPaddle = DefaultSettingsAsset->DefaultPaddleSprite;
	}
}

void UABWUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	Super::ApplySettings(bCheckForCommandLineOverrides);
}
