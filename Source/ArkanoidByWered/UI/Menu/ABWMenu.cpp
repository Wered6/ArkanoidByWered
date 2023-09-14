// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWered/UI/Menu/ABWMenu.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/EndGame/ABWEndGameWidget.h"
#include "Widgets/LevelOver/ABWLevelOverWidget.h"
#include "Widgets/MainMenu/ABWMainMenuWidget.h"

DEFINE_LOG_CATEGORY(LogMenu);

void UABWMenu::OpenMainMenuWidget()
{
	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::OpenMainMenuWidget|MainMenuWidgetClass is nullptr"));
		return;
	}

	MainMenuWidget = CreateWidget<UABWMainMenuWidget>(GetWorld(), MainMenuWidgetClass);

	if (!MainMenuWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::OpenMainMenuWidget|MainMenuWidget is nullptr"));
		return;
	}

	MainMenuWidget->AddToViewport();
}

void UABWMenu::OpenLevelOverWidget(const bool bWin)
{
	if (!LevelOverWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::OpenLevelOverWidget|LevelOverWidgetClass is nullptr"));
		return;
	}

	LevelOverWidget = CreateWidget<UABWLevelOverWidget>(GetWorld(), LevelOverWidgetClass);

	if (!LevelOverWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::OpenLevelOverWidget|LevelOverWidget is nullptr"));
		return;
	}

	LevelOverWidget->AddToViewport();

	if (bWin)
	{
		LevelOverWidget->ActivateLevelWonWidget();
	}
	else
	{
		LevelOverWidget->ActivateLevelLostWidget();
	}
}

void UABWMenu::OpenEndGameWidget()
{
	if (!EndGameWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::OpenEndGameWidget|EndGameWidgetClass is nullptr"));
		return;
	}

	EndGameWidget = CreateWidget<UABWEndGameWidget>(GetWorld(), EndGameWidgetClass);

	if (!EndGameWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::OpenEndGameWidget|EndGameWidget is nullptr"));
		return;
	}

	EndGameWidget->AddToViewport();
}
