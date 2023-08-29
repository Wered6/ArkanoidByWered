// Copyright (c) 2023 Wered. All rights reserved.


#include "MainMenuWidget.h"
#include "ArkanoidByWered/ABWUserSettings.h"
#include "ArkanoidByWered/ArkanoidDataAsset.h"
#include "Components/Image.h"
#include "PaperSprite.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> GreenAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/PaddlesAndBalls/GreenDataAsset.GreenDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> GreyAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/PaddlesAndBalls/GreyDataAsset.GreyDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> OrangeAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/PaddlesAndBalls/OrangeDataAsset.OrangeDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> PurpleAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/PaddlesAndBalls/PurpleDataAsset.PurpleDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> RedAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/PaddlesAndBalls/RedDataAsset.RedDataAsset'"));
	static ConstructorHelpers::FObjectFinder<UArkanoidDataAsset> YellowAssetFinder(
		TEXT(
			"/Script/ArkanoidByWered.ArkanoidDataAsset'/Game/Assets/DataAssets/PaddlesAndBalls/YellowDataAsset.YellowDataAsset'"));

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
	const UArkanoidDataAsset* CurrentPalette = GetCurrentPalette();
	if (!CurrentPalette)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentPalette is null!"));
		return;
	}

	if (!CurrentPalette->PaddlesSprites.IsValidIndex(PaddleIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("PaddlesIndex out of bounds!"));
		return;
	}
	UPaperSprite* PaddleSprite = CurrentPalette->PaddlesSprites[PaddleIndex];

	if (!CurrentPalette->BallsSprites.IsValidIndex(BallIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("BallIndex out of bounds"));
		return;
	}
	UPaperSprite* BallSprite = CurrentPalette->BallsSprites[BallIndex];

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

	UABWUserSettings* GameSettings = Cast<UABWUserSettings>(GEngine->GetGameUserSettings());
	if (GameSettings)
	{
		GameSettings->SelectedBall = BallSprite;
		GameSettings->SelectedPaddle = PaddleSprite;
		GameSettings->SaveSettings();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameSettings is null!"));
	}
}

void UMainMenuWidget::NextPaddle()
{
	const UArkanoidDataAsset* CurrentPalette = GetCurrentPalette();
	if (!CurrentPalette)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentPalette is null!"));
		return;
	}
	const int32 PaddlesCount = CurrentPalette->PaddlesSprites.Num();
	UpdateIndex(PaddleIndex, PaddlesCount, true);
}

void UMainMenuWidget::PreviousPaddle()
{
	const UArkanoidDataAsset* CurrentPalette = GetCurrentPalette();
	if (!CurrentPalette)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentPalette is null!"));
		return;
	}
	const int32 PaddlesCount = CurrentPalette->PaddlesSprites.Num();
	UpdateIndex(PaddleIndex, PaddlesCount, false);
}

void UMainMenuWidget::NextPalette()
{
	const int32 PalettesCount = Palettes.Num();
	UpdateIndex(PaletteIndex, PalettesCount, true);
}

void UMainMenuWidget::PreviousPalette()
{
	const int32 PalettesCount = Palettes.Num();
	UpdateIndex(PaletteIndex, PalettesCount, false);
}

const UArkanoidDataAsset* UMainMenuWidget::GetCurrentPalette()
{
	if (Palettes.IsValidIndex(PaletteIndex))
	{
		return Palettes[PaletteIndex];
	}
	UE_LOG(LogTemp, Warning, TEXT("PaletteIndex out of bounds!"));
	return nullptr;
}

void UMainMenuWidget::UpdateIndex(int32& CurrentIndex, const int32 MaxIndex, const bool bIsIncrement) const
{
	if (bIsIncrement)
	{
		CurrentIndex++;
		if (CurrentIndex > MaxIndex - 1)
		{
			CurrentIndex = 0;
		}
	}
	else
	{
		CurrentIndex--;
		if (CurrentIndex < 0)
		{
			CurrentIndex = MaxIndex - 1;
		}
	}
}
