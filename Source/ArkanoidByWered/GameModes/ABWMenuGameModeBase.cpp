// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWMenuGameModeBase.h"
#include "ArkanoidByWered/GameInstance/ABWGameInstance.h"
#include "ArkanoidByWered/UI/Menu/ABWEndGameWidget.h"
#include "ArkanoidByWered/UI/Menu/ABWMenuWidget.h"
#include "ArkanoidByWered/UI/Menu/ABWWonLostWidget.h"
#include "Blueprint/UserWidget.h"

void AABWMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Init();
	InitWidgets();
	OpenAppropriateWidget();
}

void AABWMenuGameModeBase::Init()
{
	GameInstance = Cast<UABWGameInstance>(GetGameInstance());
}

void AABWMenuGameModeBase::InitWidgets()
{
	if (!MenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWMenuGameModeBase::InitWidgets|MenuWidgetClass is null"));
		return;
	}

	MenuWidget = Cast<UABWMenuWidget>(CreateWidget(GetWorld(), MenuWidgetClass));

	if (!WonLostWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWMenuGameModeBase::InitWidgets|WonLostWidgetClass is null"));
		return;
	}

	WonLostWidget = Cast<UABWWonLostWidget>(CreateWidget(GetWorld(), WonLostWidgetClass));

	if (!EndGameWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWMenuGameModeBase::InitWidgets|EndGameWidgetClass is null"));
		return;
	}

	EndGameWidget = Cast<UABWEndGameWidget>(CreateWidget(GetWorld(), EndGameWidgetClass));
}

void AABWMenuGameModeBase::OpenAppropriateWidget() const
{
	const bool bHasCompletedAllLevels = GameInstance->GetHasCompletedAllLevels();
	const bool bIsCurrentLevelLast = GameInstance->GetIsCurrentLevelLast();
	const bool bHasPlayerStartGame = GameInstance->GetHasPlayerStartGame();
	const bool bHasPlayerWonLevel = GameInstance->GetHasPlayerWonLevel();

	if (bHasCompletedAllLevels && bIsCurrentLevelLast && bHasPlayerWonLevel)
	{
		EndGameWidget->AddToViewport();
	}
	else if (bHasPlayerStartGame)
	{
		WonLostWidget->AddToViewport();
		if (bHasPlayerWonLevel)
		{
			WonLostWidget->ActivateLevelWonWidget();
		}
		else
		{
			WonLostWidget->ActivateLevelLostWidget();
		}
	}
	else
	{
		MenuWidget->AddToViewport();
	}
}
