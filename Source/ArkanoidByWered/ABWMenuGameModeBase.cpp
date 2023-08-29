// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWMenuGameModeBase.h"
#include "GameInstance/ABWGameInstance.h"
#include "MainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"

void AABWMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Init();
	OpenMenu();
}

void AABWMenuGameModeBase::Init()
{
	GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	if (MainMenuWidgetClass)
	{
		MainMenu = Cast<UMainMenuWidget>(CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainMenuWidgetClass is null"));
	}
	if (MainMenu)
	{
		WidgetSwitcher = Cast<UWidgetSwitcher>(MainMenu->GetWidgetFromName(TEXT("WidgetSwitcher")));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainMenu is null"));
	}
}

void AABWMenuGameModeBase::OpenMenu() const
{
	if (MainMenu)
	{
		MainMenu->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainMenu is null"));
	}
	OpenAppropriateWidget();
}

void AABWMenuGameModeBase::OpenAppropriateWidget() const
{
	if (WidgetSwitcher)
	{
		if (GameInstance)
		{
			const bool bHasPlayerLost{GameInstance->GetHasPlayerLost()};
			if (bHasPlayerLost)
			{
				WidgetSwitcher->SetActiveWidgetIndex(3);
			}
			else
			{
				// todo WidgetSwitcher na Widget z "Next Level", "Menu"
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameInstance is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WidgetSwitcher is null"));
	}
}
