// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWEndGameWidget.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MainMenu/ABWMainMenuWidget.h"

void UABWEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWEndGameWidget::NativeConstruct|MenuWidgetClass is null"));
		return;
	}

	MenuWidget = Cast<UABWMainMenuWidget>(CreateWidget(GetWorld(), MenuWidgetClass));
}

void UABWEndGameWidget::OpenMenu()
{
	if (!MenuWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWEndGameWidget::OpenMenu|MenuWidget is null"));
		return;
	}

	MenuWidget->AddToViewport();
}
