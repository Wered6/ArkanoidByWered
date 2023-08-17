// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UArkanoidDataAsset;
class UPaperSprite;
class UImage;

USTRUCT(BlueprintType)
struct FPaletteSprites
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperSprite*> Paddles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Ball;
};

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

	TArray<UArkanoidDataAsset*> Palettes;

private:
	UArkanoidDataAsset* PaletteSwitcher();

	int32 PaletteIndex{0};
	int32 PaddleIndex{0};
	int32 BallIndex{0};
};
