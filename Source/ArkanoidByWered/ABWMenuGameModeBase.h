// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABWMenuGameModeBase.generated.h"

class UABWGameInstance;
class UWidgetSwitcher;
class UMainMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API AABWMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void Init();
	void OpenMenu() const;
	void OpenAppropriateWidget() const;

	UPROPERTY()
	UABWGameInstance* GameInstance;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY()
	UMainMenuWidget* MainMenu{nullptr};
	UPROPERTY()
	UWidgetSwitcher* WidgetSwitcher{nullptr};
};
