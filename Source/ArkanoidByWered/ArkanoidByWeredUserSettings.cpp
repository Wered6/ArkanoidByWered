// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWeredUserSettings.h"
#include "DefaultSettingsDataAsset.h"

UArkanoidByWeredUserSettings::UArkanoidByWeredUserSettings()
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

void UArkanoidByWeredUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	Super::ApplySettings(bCheckForCommandLineOverrides);
}
