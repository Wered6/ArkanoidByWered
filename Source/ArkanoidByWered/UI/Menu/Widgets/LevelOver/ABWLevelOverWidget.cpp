// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWLevelOverWidget.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MainMenu/ABWMainMenuWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"

void UABWLevelOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWWonLostWidget::NativeConstruct|MenuWidgetClass is null"));
		return;
	}

	MenuWidget = Cast<UABWMainMenuWidget>(CreateWidget(GetWorld(), MenuWidgetClass));
	WidSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WidgetSwitcher")));

	SetWidgets();
}

void UABWLevelOverWidget::OpenMenu()
{
	if (!MenuWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWWonLostWidget::OpenMenu|MenuWidget is null"));
		return;
	}

	MenuWidget->AddToViewport();
}

void UABWLevelOverWidget::ActivateLevelWonWidget() const
{
	if (!WidSwitcher)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|WidSwitcher is null"));
		return;
	}
	if (!LevelWonWid)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|LevelWonWid is null"));
		return;
	}

	WidSwitcher->SetActiveWidget(LevelWonWid);
}

void UABWLevelOverWidget::ActivateLevelLostWidget() const
{
	if (!WidSwitcher)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|WidSwitcher is null"));
		return;
	}
	if (!LevelLostWid)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWWonLostWidget::ActivateLevelWonWidget|LevelWonWid is null"));
		return;
	}

	WidSwitcher->SetActiveWidget(LevelLostWid);
}

void UABWLevelOverWidget::SetWidgets()
{
	LevelWonWid = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LevelWonWidget")));
	LevelLostWid = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LevelLostWidget")));
}
