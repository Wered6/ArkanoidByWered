// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWHUDWidget.h"
#include "ArkanoidByWered/DataAssets/ABWHeartsDA.h"

UABWHUDWidget::UABWHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UABWHeartsDA> HeartAssetFinder(
		TEXT("/Script/ArkanoidByWered.HeartsDA'/Game/Assets/DataAssets/Hearts/HeartsDA.HeartsDA'"));

	if (HeartAssetFinder.Succeeded())
	{
		HeartsDataAsset = HeartAssetFinder.Object;
	}
}
