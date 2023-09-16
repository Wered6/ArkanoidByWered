// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWMainMenuWidget.h"
#include "ArkanoidByWered/UI/Menu/Widgets/Levels/ABWLevelsWidget.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"

void UABWMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeLevelsWidget();
}

void UABWMainMenuWidget::OpenLevels()
{
	if (!LevelsWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMainMenuWidget::OpenLevels|LevelsWidget is nullptr"));
		return;
	}

	LevelsWidget->AddToViewport();
}


void UABWMainMenuWidget::InitializeLevelsWidget()
{
	if (!LevelsWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMainMenuWidget::InitializeLevelsWidget|LevelsWidgetClass is nullptr"));
		return;
	}

	LevelsWidget = Cast<UABWLevelsWidget>(CreateWidget(GetWorld(), LevelsWidgetClass));
}
