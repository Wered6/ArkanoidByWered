// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABWMenuGameModeBase.generated.h"

class AABWMenuPlayerController;
class UMainMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API AABWMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	
	UPROPERTY()
	UMainMenuWidget* MainMenu{nullptr};
	UPROPERTY()
	AABWMenuPlayerController* PlayerController{nullptr};
};
