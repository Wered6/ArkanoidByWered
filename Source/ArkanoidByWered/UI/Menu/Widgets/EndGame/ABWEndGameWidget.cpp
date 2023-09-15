// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWEndGameWidget.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MainMenu/ABWMainMenuWidget.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"

void UABWEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeMainMenuWidget();
}

void UABWEndGameWidget::OpenMainMenu() const
{
	if (!MainMenuWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWEndGameWidget::OpenMenu|MenuWidget is nullptr"));
		return;
	}

	MainMenuWidget->AddToViewport();
}

void UABWEndGameWidget::InitializeMainMenuWidget()
{
	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWEndGameWidget::NativeConstruct|MenuWidgetClass is nullptr"));
		return;
	}

	MainMenuWidget = Cast<UABWMainMenuWidget>(CreateWidget(GetWorld(), MainMenuWidgetClass));
}
