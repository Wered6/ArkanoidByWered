// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ABWMenu.generated.h"

class UABWEndGameWidget;
class UABWLevelOverWidget;
class UABWMainMenuWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogMenu, Log, All);

UCLASS(Blueprintable)
class ARKANOIDBYWERED_API UABWMenu : public UObject
{
	GENERATED_BODY()

public:
	void OpenMainMenuWidget();
	void OpenLevelOverWidget(const bool bWin);
	void OpenEndGameWidget();

private:
	UPROPERTY(EditDefaultsOnly, Category="Menu|MainMenu")
	TSubclassOf<UABWMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY()
	UABWMainMenuWidget* MainMenuWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|LevelOver")
	TSubclassOf<UABWLevelOverWidget> LevelOverWidgetClass;
	UPROPERTY()
	UABWLevelOverWidget* LevelOverWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="Menu|EndGame")
	TSubclassOf<UABWEndGameWidget> EndGameWidgetClass;
	UPROPERTY()
	UABWEndGameWidget* EndGameWidget{nullptr};
};
