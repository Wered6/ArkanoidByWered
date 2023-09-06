// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWUserSettings.h"
#include "ArkanoidByWered/DataAssets/ABWDefaultBallPaddleDA.h"

UABWUserSettings::UABWUserSettings()
{
	static ConstructorHelpers::FObjectFinder<UABWDefaultBallPaddleDA> DefaultSettingsAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.DefaultBallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/DefaultBallPaddleDA.DefaultBallPaddleDA'"));
	if (DefaultSettingsAssetFinder.Succeeded())
	{
		DefaultSettingsAsset = DefaultSettingsAssetFinder.Object;
		SelectedBall = DefaultSettingsAsset->DefaultBallSprite;
		SelectedPaddle = DefaultSettingsAsset->DefaultPaddleSprite;
	}
}
// todo when backing to Customize DefaultSettingsAssets are set
void UABWUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	Super::ApplySettings(bCheckForCommandLineOverrides);
}
