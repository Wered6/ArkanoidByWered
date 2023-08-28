// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWMenuGameModeBase.h"
#include "ABWMenuPlayerController.h"
#include "MainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AABWMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		MainMenu = Cast<UMainMenuWidget>(CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass));
	}
	if (MainMenu)
	{
		MainMenu->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainMenu is null"));
	}

	PlayerController = Cast<AABWMenuPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));
}
