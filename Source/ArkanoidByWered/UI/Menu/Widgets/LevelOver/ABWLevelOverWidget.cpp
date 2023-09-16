// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWLevelOverWidget.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MainMenu/ABWMainMenuWidget.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"

void UABWLevelOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeWidgetSwitcher();
}

void UABWLevelOverWidget::ActivateLevelWonWidget() const
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|WidgetSwitcher is nullptr"));
		return;
	}
	if (!LevelWonWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|LevelWonWidget is nullptr"));
		return;
	}

	WidgetSwitcher->SetActiveWidget(LevelWonWidget);
}

void UABWLevelOverWidget::ActivateLevelLostWidget() const
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|WidgetSwitcher is nullptr"));
		return;
	}
	if (!LevelLostWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|LevelLostWidget is nullptr"));
		return;
	}

	WidgetSwitcher->SetActiveWidget(LevelLostWidget);
}

void UABWLevelOverWidget::InitializeWidgetSwitcher()
{
	WidgetSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WidgetSwitcher")));

	LevelWonWidget = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LevelWonWidget")));
	LevelLostWidget = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LevelLostWidget")));
}
