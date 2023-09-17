// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWered/UI/Menu/Widgets/Customize/ABWCustomizeWidget.h"
#include "PaperSprite.h"
#include "ArkanoidByWered/DataAssets/ABWBallPaddleDA.h"
#include "ArkanoidByWered/SaveGame/ABWCustomizationSaveGame.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

UABWCustomizeWidget::UABWCustomizeWidget(const FObjectInitializer& ObjectInitializer)
{
	TArray<FString> ColorNames = {"Green", "Grey", "Orange", "Purple", "Red", "Yellow"};

	for (const auto& Color : ColorNames)
	{
		FString AssetPath = FString::Printf(
			TEXT("/Script/ArkanoidByWered.BallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/%sDA.%sDA'"), *Color,
			*Color);
		ConstructorHelpers::FObjectFinder<UABWBallPaddleDA> AssetFinder(*AssetPath);

		if (!AssetFinder.Succeeded())
		{
			UE_LOG(LogInit, Warning, TEXT("UABWMenuWidget::UABWMenuWidget|%s is invalid"), *AssetPath);
		}
		Palettes.Add(AssetFinder.Object);
	}
}

void UABWCustomizeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeGameLogic();

	SetActiveColorPalette();
}

void UABWCustomizeWidget::SetCustomization(UImage* PaddleImage, UImage* BallImage)
{
	SetActiveColorPalette();

	SetPaddleColor(PaddleImage);
	SetBallColor(BallImage);
}

void UABWCustomizeWidget::ConfirmCustomization()
{
	UPaperSprite* PaddleSprite = CurrentPalette->GetPaddleSpriteAtIndex(PaddleIndex);
	UPaperSprite* BallSprite = CurrentPalette->GetBallSpriteAtIndex(BallIndex);

	SaveGameInstance->SetPaddleSprite(PaddleSprite);
	SaveGameInstance->SetBallSprite(BallSprite);

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Slot1"), 0);
}

void UABWCustomizeWidget::ResetIndexes()
{
	PaletteIndex = 0;
	PaddleIndex = 0;
	BallIndex = 2;
}

void UABWCustomizeWidget::NextPaddle()
{
	const int32 PaddlesCount = CurrentPalette->GetPaddlesSpritesNum();
	CycleArrayIndex(PaddleIndex, PaddlesCount, true);
}

void UABWCustomizeWidget::PreviousPaddle()
{
	const int32 PaddlesCount = CurrentPalette->GetPaddlesSpritesNum();
	CycleArrayIndex(PaddleIndex, PaddlesCount, false);
}

void UABWCustomizeWidget::NextPalette()
{
	const int32 PalettesCount = Palettes.Num();
	CycleArrayIndex(PaletteIndex, PalettesCount, true);
}

void UABWCustomizeWidget::PreviousPalette()
{
	const int32 PalettesCount = Palettes.Num();
	CycleArrayIndex(PaletteIndex, PalettesCount, false);
}

void UABWCustomizeWidget::InitializeGameLogic()
{
	SaveGameInstance = Cast<UABWCustomizationSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UABWCustomizationSaveGame::StaticClass()));
}

void UABWCustomizeWidget::SetActiveColorPalette()
{
	if (!Palettes.IsValidIndex(PaletteIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWMenuWidget::SetCurrentPalette|PaletteIndex out of bounds!"));
		return;
	}

	CurrentPalette = Palettes[PaletteIndex];
}

void UABWCustomizeWidget::SetPaddleColor(UImage* PaddleImage) const
{
	UPaperSprite* PaddleSprite = CurrentPalette->GetPaddleSpriteAtIndex(PaddleIndex);

	PaddleImage->SetBrushResourceObject(PaddleSprite);
}

void UABWCustomizeWidget::SetBallColor(UImage* BallImage) const
{
	UPaperSprite* BallSprite = CurrentPalette->GetBallSpriteAtIndex(BallIndex);

	BallImage->SetBrushResourceObject(BallSprite);
}

void UABWCustomizeWidget::CycleArrayIndex(int32& CurrentIndex, const int32 MaxIndex, const bool bIsIncrement) const
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
