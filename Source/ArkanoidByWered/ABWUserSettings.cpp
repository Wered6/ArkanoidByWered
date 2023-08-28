// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWUserSettings.h"
#include "DefaultSettingsDataAsset.h"

UABWUserSettings::UABWUserSettings()
{
	static ConstructorHelpers::FObjectFinder<UDefaultSettingsDataAsset> DefaultSettingsAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.DefaultSettingsDataAsset'/Game/Assets/DataAssets/DefaultSettingsDA.DefaultSettingsDA'"));
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
