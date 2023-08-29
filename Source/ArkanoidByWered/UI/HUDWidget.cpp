// Copyright (c) 2023 Wered. All rights reserved.


#include "HUDWidget.h"
#include "ArkanoidByWered/DataAssets/HeartsDA.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UHeartsDA> HeartAssetFinder(
		TEXT("/Script/ArkanoidByWered.HeartsDA'/Game/Assets/DataAssets/Hearts/HeartsDA.HeartsDA'"));

	if (HeartAssetFinder.Succeeded())
	{
		HeartsDataAsset = HeartAssetFinder.Object;
	}
}
