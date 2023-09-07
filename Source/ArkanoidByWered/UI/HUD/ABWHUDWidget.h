// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWHUDWidget.generated.h"

class UABWHeartsDA;

UCLASS()
class ARKANOIDBYWERED_API UABWHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UABWHUDWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, Transient, Category="Animations", meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation1{nullptr};
	UPROPERTY(BlueprintReadOnly, Transient, Category="Animations", meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation2{nullptr};
	UPROPERTY(BlueprintReadOnly, Transient, Category="Animations", meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation3{nullptr};

private:
	UPROPERTY()
	UABWHeartsDA* HeartsDataAsset{nullptr};
};
