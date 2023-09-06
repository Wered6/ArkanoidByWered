// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWEndGameWidget.h"
#include "ABWMenuWidget.h"

void UABWEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWEndGameWidget::NativeConstruct|MenuWidgetClass is null"));
		return;
	}

	MenuWidget = Cast<UABWMenuWidget>(CreateWidget(GetWorld(), MenuWidgetClass));
}

void UABWEndGameWidget::OpenMenu()
{
	if (!MenuWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWEndGameWidget::OpenMenu|MenuWidget is null"));
		return;
	}

	MenuWidget->AddToViewport();
	this->RemoveFromParent();
}
