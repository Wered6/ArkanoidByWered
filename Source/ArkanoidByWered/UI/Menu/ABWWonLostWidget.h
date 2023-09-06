// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWWonLostWidget.generated.h"

class UCanvasPanel;
class UWidgetSwitcher;
class UABWMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API UABWWonLostWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|Menu")
	void OpenMenu();

	void ActivateLevelWonWidget() const;
	void ActivateLevelLostWidget() const;

private:
	void SetWidgets();

	UPROPERTY(EditDefaultsOnly, Category="UI|Menu")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY()
	UABWMenuWidget* MenuWidget{nullptr};

	UPROPERTY()
	UWidgetSwitcher* WidSwitcher{nullptr};

	UPROPERTY()
	UCanvasPanel* LevelWonWid{nullptr};
	UPROPERTY()
	UCanvasPanel* LevelLostWid{nullptr};
};
