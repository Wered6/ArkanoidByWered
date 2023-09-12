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
	check(CheckNullPointers());
	OpenAppropriateWidget();
}

void AABWMenuGameModeBase::Init()
{
	GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	check(CheckNullClasses());
	InitWidgets();
}

void AABWMenuGameModeBase::InitWidgets()
{
	MenuWidget = Cast<UABWMenuWidget>(CreateWidget(GetWorld(), MenuWidgetClass));
	WonLostWidget = Cast<UABWWonLostWidget>(CreateWidget(GetWorld(), WonLostWidgetClass));
	EndGameWidget = Cast<UABWEndGameWidget>(CreateWidget(GetWorld(), EndGameWidgetClass));
}

bool AABWMenuGameModeBase::CheckNullClasses() const
{
	if (!MenuWidgetClass)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::CheckNullClasses|MenuWidgetClass is null"));
		return false;
	}
	if (!WonLostWidgetClass)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::CheckNullClasses|WonLostWidgetClass is null"));
		return false;
	}
	if (!EndGameWidgetClass)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::CheckNullClasses|EndGameWidgetClass is null"));
		return false;
	}
	return true;
}

bool AABWMenuGameModeBase::CheckNullPointers() const
{
	if (!GameInstance)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::CheckNullPointers|GameInstance is null"));
		return false;
	}
	if (!MenuWidget)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::CheckNullPointers|MenuWidget is null"));
		return false;
	}
	if (!WonLostWidget)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::CheckNullPointers|WonLostWidget is null"));
		return false;
	}
	if (!EndGameWidget)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::CheckNullPointers|EndGameWidget is null"));
		return false;
	}
	return true;
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
