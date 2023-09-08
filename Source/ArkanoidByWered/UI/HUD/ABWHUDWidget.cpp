// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWHUDWidget.h"

void UABWHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HeartsAnimations.Add(HeartAnimation1);
	HeartsAnimations.Add(HeartAnimation2);
	HeartsAnimations.Add(HeartAnimation3);
}

void UABWHUDWidget::PlayHeartEmptyAnimaion(const int32 Lifes)
{
	const int32 AnimationIndex = Lifes - 1;

	if (!HeartsAnimations.IsValidIndex(AnimationIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWHUDWidget::PlayHeartEmptyAnimaion|AnimationIndex out of bounds!"));
		return;
	}

	PlayAnimation(HeartsAnimations[AnimationIndex]);
}

void UABWHUDWidget::PlayHeartFillAnimaion(const int32 Lifes)
{
	const int32 AnimationIndex = Lifes;

	if (!HeartsAnimations.IsValidIndex(AnimationIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWHUDWidget::PlayHeartFillAnimaion|AnimationIndex out of bounds!"));
		return;
	}

	PlayAnimation(HeartsAnimations[AnimationIndex], 0, 1, EUMGSequencePlayMode::Reverse);
}
