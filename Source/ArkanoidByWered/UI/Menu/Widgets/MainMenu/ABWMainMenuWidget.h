// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MenuBase/ABWMenuBaseWidget.h"
#include "ABWMainMenuWidget.generated.h"

class UABWLevelsWidget;
class UABWCustomizationSaveGame;
class UABWLevelSubsystem;
class UButton;
class UABWBallPaddleDA;
class UImage;

UCLASS()
class ARKANOIDBYWERED_API UABWMainMenuWidget : public UABWMenuBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|Levels")
	void OpenLevels();

private:
	void InitializeLevelsWidget();

	UPROPERTY(EditDefaultsOnly, Category="UI|Levels")
	TSubclassOf<UABWLevelsWidget> LevelsWidgetClass;
	UPROPERTY()
	UABWLevelsWidget* LevelsWidget{nullptr};
};
