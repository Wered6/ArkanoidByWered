// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MenuBase/ABWMenuBaseWidget.h"
#include "ABWCustomizeWidget.generated.h"

class UImage;
class UABWCustomizationSaveGame;
class UABWBallPaddleDA;

UCLASS()
class ARKANOIDBYWERED_API UABWCustomizeWidget : public UABWMenuBaseWidget
{
	GENERATED_BODY()

public:
	UABWCustomizeWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

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

	void SetActiveColorPalette();

	void SetPaddleColor(UImage* PaddleImage) const;
	void SetBallColor(UImage* BallImage) const;

	void CycleArrayIndex(int32& CurrentIndex, const int32 MaxIndex, const bool bIsIncrement) const;

	UPROPERTY()
	TArray<UABWBallPaddleDA*> Palettes;
	int32 PaletteIndex{0};
	int32 PaddleIndex{0};
	int32 BallIndex{2};

	UPROPERTY()
	UABWBallPaddleDA* CurrentPalette{nullptr};

	UPROPERTY()
	UABWCustomizationSaveGame* SaveGameInstance{nullptr};
};
