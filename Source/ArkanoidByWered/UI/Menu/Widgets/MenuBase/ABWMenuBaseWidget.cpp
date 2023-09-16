// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWered/UI/Menu/Widgets/MenuBase/ABWMenuBaseWidget.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MainMenu/ABWMainMenuWidget.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"

void UABWMenuBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeMainMenuWidget();
}

void UABWMenuBaseWidget::OpenMainMenu() const
{
	if (!MainMenuWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenuBaseWidget::OpenMainMenu|MainMenuWidgetClass is nullptr"));
		return;
	}

	MainMenuWidget->AddToViewport();
}

void UABWMenuBaseWidget::InitializeMainMenuWidget()
{
	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMenuBaseWidget::InitializeMainMenuWidget|MainMenuWidgetClass is nullptr"));
		return;
	}

	MainMenuWidget = Cast<UABWMainMenuWidget>(CreateWidget(GetWorld(), MainMenuWidgetClass));
}
