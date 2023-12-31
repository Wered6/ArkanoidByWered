// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWHeartsWidget.generated.h"

class UABWHeartsDA;

UCLASS()
class ARKANOIDBYWERED_API UABWHeartsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void PlayEmptyAnimation(const int32 CurrentLifes);
	void PlayFillAnimation(const int32 CurrentLifes);

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation1{nullptr};
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation2{nullptr};
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* HeartAnimation3{nullptr};

private:
	UPROPERTY()
	TArray<UWidgetAnimation*> HeartsAnimations;
};
