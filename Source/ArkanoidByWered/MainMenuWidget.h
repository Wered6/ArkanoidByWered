// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UArkanoidDataAsset;
class UImage;

UCLASS()
class ARKANOIDBYWERED_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

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

private:
	const UArkanoidDataAsset* GetCurrentPalette();
	void UpdateIndex(int32& CurrentIndex, const int32 MaxIndex, const bool bIsIncrement) const;

	TArray<UArkanoidDataAsset*> Palettes;
	int32 PaletteIndex{0};
	int32 PaddleIndex{0};
	int32 BallIndex{0};
};
