// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Image.h"
#include "PaperSprite.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ColorPalettes =
	{
		&GreenSprites,
		&GreySprites,
		&OrangeSprites,
		&PurpleSprites,
		&RedSprites,
		&YellowSprites
	};
}

void UMainMenuWidget::SetCustomization(UImage* PaddleImage, UImage* BallImage)
{
	auto [PaddlesSprites, BallSprite] = PaletteSwitcher();
	UPaperSprite* PaddleSprite = PaddlesSprites[PaddleIndex];

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
}

void UMainMenuWidget::NextPaddle()
{
	const auto [PaddlesSprites, BallSprite] = PaletteSwitcher();
	const int32 PaddlesCount = PaddlesSprites.Num();

	PaddleIndex++;
	if (PaddleIndex > PaddlesCount - 1)
	{
		PaddleIndex = 0;
	}
}

void UMainMenuWidget::PreviousPaddle()
{
	const auto [PaddlesSprites, BallSprite] = PaletteSwitcher();
	const int32 PaddlesCount = PaddlesSprites.Num();

	PaddleIndex--;
	if (PaddleIndex < 0)
	{
		PaddleIndex = PaddlesCount - 1;
	}
}

void UMainMenuWidget::NextPalette()
{
	const int32 PalettesCount = ColorPalettes.Num();

	PaletteIndex++;
	if (PaletteIndex > PalettesCount - 1)
	{
		PaletteIndex = 0;
	}
}

void UMainMenuWidget::PreviousPalette()
{
	const int32 PalettesCount = ColorPalettes.Num();

	PaletteIndex--;
	if (PaletteIndex < 0)
	{
		PaletteIndex = PalettesCount - 1;
	}
}

FPaletteSprites UMainMenuWidget::PaletteSwitcher()
{
	return *ColorPalettes[PaletteIndex];
}
