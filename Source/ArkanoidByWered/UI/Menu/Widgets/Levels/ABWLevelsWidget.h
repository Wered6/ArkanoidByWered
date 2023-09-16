// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWLevelsWidget.generated.h"

class UABWMainMenuWidget;
class UABWLevelSubsystem;
class UButton;

UCLASS()
class ARKANOIDBYWERED_API UABWLevelsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|Menu")
	void OpenMainMenu() const;

private:
	void InitializeGameLogic();
	void InitializeLevelsButtons();	
	void InitializeMainMenuWidget();

	UPROPERTY(EditDefaultsOnly, Category="UI|Menu")
	TSubclassOf<UABWMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY()
	UABWMainMenuWidget* MainMenuWidget{nullptr};

	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem{nullptr};
};
