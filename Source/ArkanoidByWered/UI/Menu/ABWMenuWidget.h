// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidByWered/DataAssets/ABWBallPaddleDA.h"
#include "Blueprint/UserWidget.h"
#include "ABWMenuWidget.generated.h"

class UABWUserSettings;
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
	void NextPaddle();
	UFUNCTION(BlueprintCallable)
	void PreviousPaddle();

	UFUNCTION(BlueprintCallable)
	void NextPalette();
	UFUNCTION(BlueprintCallable)
	void PreviousPalette();

	void SetLevelButtons();
	void SetLevelButtonsAvailability() const;

private:
	void SetCurrentPalette();

	void SetPaddleColor(UImage* PaddleImage) const;
	void SetBallColor(UImage* BallImage) const;

	void UpdateIndex(int32& CurrentIndex, const int32 MaxIndex, const bool bIsIncrement) const;

	UPROPERTY()
	TArray<UABWBallPaddleDA*> Palettes;
	int32 PaletteIndex{0};
	int32 PaddleIndex{0};
	int32 BallIndex{0};

	UPROPERTY()
	UABWBallPaddleDA* CurrentPalette{nullptr};
	UPROPERTY()
	UABWUserSettings* GameSettings{nullptr};

	UPROPERTY()
	UButton* Level1Button{nullptr};
	UPROPERTY()
	UButton* Level2Button{nullptr};
	UPROPERTY()
	UButton* Level3Button{nullptr};

	UPROPERTY()
	UABWLevelSubsystem* LevelSubsystem{nullptr};
};
