// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWLevelOverWidget.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MainMenu/ABWMainMenuWidget.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"

void UABWLevelOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeMainMenuWidget();
	InitializeWidgetSwitcher();
}

void UABWLevelOverWidget::OpenMainMenu() const
{
	if (!MainMenuWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::OpenMenu|MenuWidget is null"));
		return;
	}

	MainMenuWidget->AddToViewport();
}

void UABWLevelOverWidget::ActivateLevelWonWidget() const
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|WidSwitcher is null"));
		return;
	}
	if (!LevelWonWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|LevelWonWid is null"));
		return;
	}

	WidgetSwitcher->SetActiveWidget(LevelWonWidget);
}

void UABWLevelOverWidget::ActivateLevelLostWidget() const
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|WidSwitcher is null"));
		return;
	}
	if (!LevelLostWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|LevelWonWid is null"));
		return;
	}

	WidgetSwitcher->SetActiveWidget(LevelLostWidget);
}

void UABWLevelOverWidget::InitializeMainMenuWidget()
{
	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::NativeConstruct|MenuWidgetClass is null"));
		return;
	}

	MainMenuWidget = Cast<UABWMainMenuWidget>(CreateWidget(GetWorld(), MainMenuWidgetClass));
}

void UABWLevelOverWidget::InitializeWidgetSwitcher()
{
	WidgetSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WidgetSwitcher")));

	LevelWonWidget = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LevelWonWidget")));
	LevelLostWidget = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LevelLostWidget")));
}
