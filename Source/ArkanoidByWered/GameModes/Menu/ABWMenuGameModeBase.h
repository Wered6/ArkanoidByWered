// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABWMenuGameModeBase.generated.h"

class UABWGameInstance;
class UABWEndGameWidget;
class UABWWonLostWidget;
class UABWMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API AABWMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void Init();
	void InitWidgets();
	bool CheckNullClasses() const;
	bool CheckNullPointers() const;

	void OpenAppropriateWidget() const;

	UPROPERTY(EditDefaultsOnly, Category="UI|Menu")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY()
	UABWMenuWidget* MenuWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="UI|Menu")
	TSubclassOf<UUserWidget> WonLostWidgetClass;
	UPROPERTY()
	UABWWonLostWidget* WonLostWidget{nullptr};

	UPROPERTY(EditDefaultsOnly, Category="UI|Menu")
	TSubclassOf<UUserWidget> EndGameWidgetClass;
	UPROPERTY()
	UABWEndGameWidget* EndGameWidget{nullptr};

	UPROPERTY()
	UABWGameInstance* GameInstance{nullptr};
};
