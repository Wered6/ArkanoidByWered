// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWHeartsWidget.h"
#include "ArkanoidByWered/UI/HUD/ABWHUD.h"

void UABWHeartsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HeartsAnimations.Add(HeartAnimation1);
	HeartsAnimations.Add(HeartAnimation2);
	HeartsAnimations.Add(HeartAnimation3);
}

void UABWHeartsWidget::PlayEmptyAnimation(const int32 CurrentLifes)
{
	const int32 AnimationIndex = CurrentLifes - 1;

	if (!HeartsAnimations.IsValidIndex(AnimationIndex))
	{
		UE_LOG(LogHUD, Warning, TEXT("UABWHUDWidget::PlayHeartEmptyAnimaion|AnimationIndex out of bounds!"));
		return;
	}

	PlayAnimation(HeartsAnimations[AnimationIndex]);
}

void UABWHeartsWidget::PlayFillAnimation(const int32 CurrentLifes)
{
	const int32 AnimationIndex = CurrentLifes;

	if (!HeartsAnimations.IsValidIndex(AnimationIndex))
	{
		UE_LOG(LogHUD, Warning, TEXT("UABWHUDWidget::PlayHeartFillAnimaion|AnimationIndex out of bounds!"));
		return;
	}

	PlayAnimation(HeartsAnimations[AnimationIndex], 0, 1, EUMGSequencePlayMode::Reverse);
}
