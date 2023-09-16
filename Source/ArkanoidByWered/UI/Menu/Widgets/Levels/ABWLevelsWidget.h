// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MenuBase/ABWMenuBaseWidget.h"
#include "ABWLevelsWidget.generated.h"

class UABWMainMenuWidget;
class UABWLevelSubsystem;
class UButton;

UCLASS()
class ARKANOIDBYWERED_API UABWLevelsWidget : public UABWMenuBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	void InitializeGameLogic();
	void UpdateLevelsButtonsStates();

	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem{nullptr};
};
