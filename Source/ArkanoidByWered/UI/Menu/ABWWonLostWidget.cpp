// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWWonLostWidget.h"
#include "ABWMenuWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"

void UABWWonLostWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWWonLostWidget::NativeConstruct|MenuWidgetClass is null"));
		return;
	}

	MenuWidget = Cast<UABWMenuWidget>(CreateWidget(GetWorld(), MenuWidgetClass));
	WidSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WidgetSwitcher")));

	SetWidgets();
}

void UABWWonLostWidget::OpenMenu()
{
	if (!MenuWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWWonLostWidget::OpenMenu|MenuWidget is null"));
		return;
	}

	MenuWidget->AddToViewport();
	this->RemoveFromParent();
}

void UABWWonLostWidget::ActivateLevelWonWidget() const
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

void UABWWonLostWidget::ActivateLevelLostWidget() const
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

void UABWWonLostWidget::SetWidgets()
{
	LevelWonWid = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LevelWonWidget")));
	LevelLostWid = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("LevelLostWidget")));
}
