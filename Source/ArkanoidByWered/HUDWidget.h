// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UHeartsDataAsset;

UCLASS()
class ARKANOIDBYWERED_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHUDWidget(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY()
	UHeartsDataAsset* HeartsDataAsset;
};
