// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWered/UI/Menu/ABWMenu.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/EndGame/ABWEndGameWidget.h"
#include "Widgets/LevelOver/ABWLevelOverWidget.h"
#include "Widgets/MainMenu/ABWMainMenuWidget.h"

void UABWMenu::InitializeWidgets()
{
	InitializeMainMenuWidget();
	InitializeLevelOverWidget();
	InitializeEndGameWidget();
}

void UABWMenu::OpenMainMenuWidget()
{
	if (!MainMenuWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::OpenMainMenuWidget|MainMenuWidget is nullptr"));
		return;
	}

	MainMenuWidget->AddToViewport();
}

void UABWMenu::OpenLevelOverWidget(const bool bWin)
{
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
	if (!EndGameWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::OpenEndGameWidget|EndGameWidget is nullptr"));
		return;
	}

	EndGameWidget->AddToViewport();
}

void UABWMenu::InitializeMainMenuWidget()
{
	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::InitializeMainMenuWidget|MainMenuWidgetClass is nullptr"));
		return;
	}

	MainMenuWidget = CreateWidget<UABWMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
}

void UABWMenu::InitializeLevelOverWidget()
{
	if (!LevelOverWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::InitializeLevelOverWidget|LevelOverWidgetClass is nullptr"));
		return;
	}

	LevelOverWidget = CreateWidget<UABWLevelOverWidget>(GetWorld(), LevelOverWidgetClass);
}

void UABWMenu::InitializeEndGameWidget()
{
	if (!EndGameWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenu::InitializeEndGameWidget|EndGameWidgetClass is nullptr"));
		return;
	}

	EndGameWidget = CreateWidget<UABWEndGameWidget>(GetWorld(), EndGameWidgetClass);
}
