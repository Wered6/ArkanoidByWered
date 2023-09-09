// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidByWered/DataAssets/ABWBallPaddleDA.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "ABWMenuWidget.generated.h"

class UABWCustomizationSaveGame;
class UABWLevelSubsystem;
class UButton;
class UABWBallPaddleDA;
class UImage;

UCLASS()
class ARKANOIDBYWERED_API UABWMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UABWMenuWidget(const FObjectInitializer& ObjectInitializer);

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
	void Init();
	void SetLevelButtons();
	void UpdateLevelButtonStates() const;
	void SetActiveColorPalette();
	bool AreRequiredPointersValid() const;

	void SetPaddleColor(UImage* PaddleImage) const;
	void SetBallColor(UImage* BallImage) const;

	void CycleArrayIndex(int32& CurrentIndex, const int32 MaxIndex, const bool bIsIncrement) const;

	UPROPERTY()
	TArray<UABWBallPaddleDA*> Palettes;
	int32 PaletteIndex{0};
	int32 PaddleIndex{0};
	int32 BallIndex{0};

	UPROPERTY()
	UABWBallPaddleDA* CurrentPalette{nullptr};

	UPROPERTY()
	UButton* Level1Button{nullptr};
	UPROPERTY()
	UButton* Level2Button{nullptr};
	UPROPERTY()
	UButton* Level3Button{nullptr};

	UPROPERTY()
	UABWCustomizationSaveGame* SaveGameInstance{nullptr};
	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem{nullptr};
};
