// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MenuBase/ABWMenuBaseWidget.h"
#include "ABWLevelOverWidget.generated.h"

class UCanvasPanel;
class UWidgetSwitcher;
class UABWMainMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API UABWLevelOverWidget : public UABWMenuBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void ActivateLevelWonWidget() const;
	void ActivateLevelLostWidget() const;

private:
	void InitializeWidgetSwitcher();
	
	UPROPERTY()
	UWidgetSwitcher* WidgetSwitcher{nullptr};

	UPROPERTY()
	UCanvasPanel* LevelWonWidget{nullptr};
	UPROPERTY()
	UCanvasPanel* LevelLostWidget{nullptr};
};
