// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWMenuBaseWidget.generated.h"

class UABWMainMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API UABWMenuBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|Menu")
	virtual void OpenMainMenu() const;

private:
	void InitializeMainMenuWidget();

	UPROPERTY(EditDefaultsOnly, Category="UI|Menu")
	TSubclassOf<UABWMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY()
	UABWMainMenuWidget* MainMenuWidget;
};
