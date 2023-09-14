// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ABWHUD.generated.h"

class UABWHeartsWidget;

UCLASS()
class ARKANOIDBYWERED_API AABWHUD : public AHUD
{
	GENERATED_BODY()

public:
	void AddToViewport();

	void PlayHeartAnimation(const int32 CurrentLifes, const bool bFill);

private:
	UPROPERTY(EditDefaultsOnly, Category="Hearts")
	TSubclassOf<UABWHeartsWidget> HeartsWidgetClass;
	UPROPERTY()
	UABWHeartsWidget* HeartsWidget{nullptr};
};
