// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWHUD.h"
#include "ArkanoidByWered/Utilities/ABWUtilities.h"
#include "Widgets/Hearts/ABWHeartsWidget.h"

void AABWHUD::AddToViewport()
{
	if (!HeartsWidgetClass)
	{
		UE_LOG(LogHUD, Warning, TEXT("AABWHUD::AddToViewport|HeartsWidgetClass is nullptr"));
		return;
	}

	HeartsWidget = CreateWidget<UABWHeartsWidget>(GetWorld(), HeartsWidgetClass);

	if (!HeartsWidget)
	{
		UE_LOG(LogHUD, Warning, TEXT("AABWHUD::AddToViewport|HeartsWidget is nullptr"));
		return;
	}

	HeartsWidget->AddToViewport();
}

void AABWHUD::PlayHeartAnimation(const int32 CurrentLifes, const bool bFill)
{
	if (!HeartsWidget)
	{
		UE_LOG(LogHUD, Warning, TEXT("AABWHUD::PlayerHeartFillAnimation|HeartsWidget is nullptr"))
		return;
	}

	if (bFill)
	{
		HeartsWidget->PlayFillAnimation(CurrentLifes);
	}
	else
	{
		HeartsWidget->PlayEmptyAnimation(CurrentLifes);
	}
}
