// Copyright (c) 2023 Wered. All rights reserved.


#include "HUDWidget.h"
#include "ArkanoidByWered/HeartsDataAsset.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UHeartsDataAsset> HeartAssetFinder(
		TEXT("/Script/ArkanoidByWered.HeartsDataAsset'/Game/Assets/DataAssets/HeartsDataAsset.HeartsDataAsset'"));

	if (HeartAssetFinder.Succeeded())
	{
		HeartsDataAsset = HeartAssetFinder.Object;
	}
}
