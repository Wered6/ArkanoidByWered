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

	UPROPERTY(BlueprintReadOnly, Transient, Category="Animations", meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation1;
	UPROPERTY(BlueprintReadOnly, Transient, Category="Animations", meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation2;
	UPROPERTY(BlueprintReadOnly, Transient, Category="Animations", meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation3;

private:
	UPROPERTY()
	UHeartsDataAsset* HeartsDataAsset;
};
