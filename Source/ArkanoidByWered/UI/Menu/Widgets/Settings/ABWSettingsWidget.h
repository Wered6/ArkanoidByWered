// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MenuBase/ABWMenuBaseWidget.h"
#include "ABWSettingsWidget.generated.h"

class UABWCustomizeWidget;

UCLASS()
class ARKANOIDBYWERED_API UABWSettingsWidget : public UABWMenuBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|Customize")
	void OpenCustomize() const;

private:
	void InitializeCustomizeWidget();

	UPROPERTY(EditDefaultsOnly, Category="UI|Customize")
	TSubclassOf<UABWCustomizeWidget> CustomizeWidgetClass;
	UPROPERTY()
	UABWCustomizeWidget* CustomizeWidget{nullptr};
};
