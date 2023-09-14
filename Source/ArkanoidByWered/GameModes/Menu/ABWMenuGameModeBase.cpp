// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWMenuGameModeBase.h"
#include "ArkanoidByWered/GameInstance/ABWGameInstance.h"
#include "ArkanoidByWered/UI/Menu/ABWMenu.h"

void AABWMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Init();
	OpenAppropriateWidget();
}

void AABWMenuGameModeBase::Init()
{
	if (!MenuClass)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::Init|MenuClass is nullptr"));
		return;
	}
	
	Menu = NewObject<UABWMenu>(this, MenuClass);
	GameInstance = Cast<UABWGameInstance>(GetGameInstance());
}

void AABWMenuGameModeBase::OpenAppropriateWidget() const
{
	if (!GameInstance)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::OpenAppropriateWidget|GameInstance is nullptr"));
		return;
	}
	if (!Menu)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWMenuGameModeBase::OpenAppropriateWidget|Menu is nullptr"));
		return;
	}

	const bool bHasCompletedAllLevels = GameInstance->GetHasCompletedAllLevels();
	const bool bIsCurrentLevelLast = GameInstance->GetIsCurrentLevelLast();
	const bool bHasPlayerStartGame = GameInstance->GetHasPlayerStartGame();
	const bool bHasPlayerWonLevel = GameInstance->GetHasPlayerWonLevel();

	if (bHasCompletedAllLevels && bIsCurrentLevelLast && bHasPlayerWonLevel)
	{
		Menu->OpenEndGameWidget();
	}
	else if (bHasPlayerStartGame)
	{
		Menu->OpenLevelOverWidget(bHasPlayerWonLevel);
	}
	else
	{
		Menu->OpenMainMenuWidget();
	}
}
