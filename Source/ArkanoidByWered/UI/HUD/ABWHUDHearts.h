// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWHUDHearts.generated.h"

class UABWHeartsDA;

UCLASS()
class ARKANOIDBYWERED_API UABWHUDHearts : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void PlayHeartEmptyAnimaion(const int32 Lifes);
	void PlayHeartFillAnimaion(const int32 Lifes);

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
