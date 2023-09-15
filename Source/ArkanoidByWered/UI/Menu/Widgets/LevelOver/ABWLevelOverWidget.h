// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWLevelOverWidget.generated.h"

class UCanvasPanel;
class UWidgetSwitcher;
class UABWMainMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API UABWLevelOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|Menu")
	void OpenMainMenu() const;

	void ActivateLevelWonWidget() const;
	void ActivateLevelLostWidget() const;

private:
	void InitializeMainMenuWidget();
	void InitializeWidgetSwitcher();
	
	UPROPERTY(EditDefaultsOnly, Category="UI|Menu")
	TSubclassOf<UABWMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY()
	UABWMainMenuWidget* MainMenuWidget{nullptr};

	UPROPERTY()
	UWidgetSwitcher* WidgetSwitcher{nullptr};

	UPROPERTY()
	UCanvasPanel* LevelWonWidget{nullptr};
	UPROPERTY()
	UCanvasPanel* LevelLostWidget{nullptr};
};
