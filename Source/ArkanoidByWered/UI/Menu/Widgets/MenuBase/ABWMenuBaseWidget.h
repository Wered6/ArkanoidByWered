// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWMenuBaseWidget.generated.h"

class UABWSettingsWidget;
class UABWMainMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API UABWMenuBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|MainMenu")
	virtual void OpenMainMenu() const;
	UFUNCTION(BlueprintCallable, Category="UI|Settings")
	virtual void OpenSettings() const;

private:
	void InitializeMainMenuWidget();
	void InitializeSettingsWidget();

	UPROPERTY(EditDefaultsOnly, Category="UI|MainMenu")
	TSubclassOf<UABWMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY()
	UABWMainMenuWidget* MainMenuWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="UI|Settings")
	TSubclassOf<UABWSettingsWidget> SettingsWidgetClass;
	UPROPERTY()
	UABWSettingsWidget* SettingsWidget{nullptr};
};
