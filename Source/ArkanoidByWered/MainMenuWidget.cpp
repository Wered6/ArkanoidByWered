// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "ArkanoidByWeredUserSettings.h"
#include "ArkanoidDataAsset.h"
#include "Components/Image.h"
#include "PaperSprite.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> GreenAssetFinder(
		TEXT("/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/GreenDataAsset.GreenDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> GreyAssetFinder(
		TEXT("/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/GreyDataAsset.GreyDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> OrangeAssetFinder(
		TEXT("/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/OrangeDataAsset.OrangeDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> PurpleAssetFinder(
		TEXT("/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/PurpleDataAsset.PurpleDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> RedAssetFinder(
		TEXT("/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/RedDataAsset.RedDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> YellowAssetFinder(
		TEXT("/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/YellowDataAsset.YellowDataAsset'"));

	if (GreenAssetFinder.Succeeded() && GreyAssetFinder.Succeeded() && OrangeAssetFinder.Succeeded() &&
		PurpleAssetFinder.Succeeded() && RedAssetFinder.Succeeded() && YellowAssetFinder.Succeeded())
	{
		
		Palettes.Add(GreenAssetFinder.Object);
		Palettes.Add(GreyAssetFinder.Object);
		Palettes.Add(OrangeAssetFinder.Object);
		Palettes.Add(PurpleAssetFinder.Object);
		Palettes.Add(RedAssetFinder.Object);
		Palettes.Add(YellowAssetFinder.Object);
	}
}

void UMainMenuWidget::SetCustomization(UImage* PaddleImage, UImage* BallImage)
{
	UArkanoidDataAsset* CurrentPallete = PaletteSwitcher();
	UPaperSprite* PaddleSprite = CurrentPallete->PaddlesSprites[PaddleIndex];
	UPaperSprite* BallSprite = CurrentPallete->BallsSprites[BallIndex];

	if (PaddleSprite)
	{
		PaddleImage->SetBrushResourceObject(PaddleSprite);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PaddleSprite is null!"));
	}

	if (BallSprite)
	{
		BallImage->SetBrushResourceObject(BallSprite);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BallSprite is null!"));
	}

	UArkanoidByWeredUserSettings* GameSettings = Cast<UArkanoidByWeredUserSettings>(GEngine->GetGameUserSettings());
	if (GameSettings)
	{
		GameSettings->SelectedBall = BallSprite;
		GameSettings->SelectedPaddle = PaddleSprite;
		GameSettings->SaveSettings();
	}
}

void UMainMenuWidget::NextPaddle()
{
	const UArkanoidDataAsset* CurrentPallete = PaletteSwitcher();
	const int32 PaddlesCount = CurrentPallete->PaddlesSprites.Num();

	PaddleIndex++;
	if (PaddleIndex > PaddlesCount - 1)
	{
		PaddleIndex = 0;
	}
}

void UMainMenuWidget::PreviousPaddle()
{
	const UArkanoidDataAsset* CurrentPallete = PaletteSwitcher();
	const int32 PaddlesCount = CurrentPallete->PaddlesSprites.Num();

	PaddleIndex--;
	if (PaddleIndex < 0)
	{
		PaddleIndex = PaddlesCount - 1;
	}
}

void UMainMenuWidget::NextPalette()
{
	const int32 PalettesCount = Palettes.Num();

	PaletteIndex++;
	if (PaletteIndex > PalettesCount - 1)
	{
		PaletteIndex = 0;
	}
}

void UMainMenuWidget::PreviousPalette()
{
	const int32 PalettesCount = Palettes.Num();

	PaletteIndex--;
	if (PaletteIndex < 0)
	{
		PaletteIndex = PalettesCount - 1;
	}
}

UArkanoidDataAsset* UMainMenuWidget::PaletteSwitcher()
{
	return Palettes[PaletteIndex];
}
