// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidByWered/DataAssets/ABWBallPaddleDA.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MenuBase/ABWMenuBaseWidget.h"
#include "Components/Image.h"
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
	UABWMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|Levels")
	void OpenLevels();

	UFUNCTION(BlueprintCallable)
	void SetCustomization(UImage* PaddleImage, UImage* BallImage);
	UFUNCTION(BlueprintCallable)
	void ConfirmCustomization();
	UFUNCTION(BlueprintCallable)
	void ResetIndexes();

	UFUNCTION(BlueprintCallable)
	void NextPaddle();
	UFUNCTION(BlueprintCallable)
	void PreviousPaddle();

	UFUNCTION(BlueprintCallable)
	void NextPalette();
	UFUNCTION(BlueprintCallable)
	void PreviousPalette();

private:
	void InitializeGameLogic();
	void InitializeLevelsWidget();

	void SetActiveColorPalette();

	void SetPaddleColor(UImage* PaddleImage) const;
	void SetBallColor(UImage* BallImage) const;

	void CycleArrayIndex(int32& CurrentIndex, const int32 MaxIndex, const bool bIsIncrement) const;

	UPROPERTY(EditDefaultsOnly, Category="UI|Levels")
	TSubclassOf<UABWLevelsWidget> LevelsWidgetClass;
	UPROPERTY()
	UABWLevelsWidget* LevelsWidget{nullptr};

	UPROPERTY()
	TArray<UABWBallPaddleDA*> Palettes;
	int32 PaletteIndex{0};
	int32 PaddleIndex{0};
	int32 BallIndex{2};

	UPROPERTY()
	UABWBallPaddleDA* CurrentPalette{nullptr};

	UPROPERTY()
	UABWCustomizationSaveGame* SaveGameInstance{nullptr};
	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem{nullptr};
};
