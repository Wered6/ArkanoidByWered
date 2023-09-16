// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWered/UI/Menu/Widgets/Settings/ABWSettingsWidget.h"
#include "ArkanoidByWered/UI/Menu/Widgets/Customize/ABWCustomizeWidget.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"

void UABWSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeCustomizeWidget();
}

void UABWSettingsWidget::OpenCustomize() const
{
	if (!CustomizeWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWSettingsWidget::OpenCustomize|CustomizeWidget is nullptr"));
		return;
	}

	CustomizeWidget->AddToViewport();
}

void UABWSettingsWidget::InitializeCustomizeWidget()
{
	if (!CustomizeWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWSettingsWidget::InitializeCustomizeWidget|CustomizeWidgetClass is nullptr"));
		return;
	}

	CustomizeWidget = Cast<UABWCustomizeWidget>(CreateWidget(GetWorld(), CustomizeWidgetClass));
}
