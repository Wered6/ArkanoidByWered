// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWMainMenuWidget.h"
#include "ArkanoidByWered/DataAssets/ABWBallPaddleDA.h"
#include "Components/Image.h"
#include "PaperSprite.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelSubsystem.h"
#include "ArkanoidByWered/GameInstance/ABWGameInstance.h"
#include "ArkanoidByWered/SaveGame/ABWCustomizationSaveGame.h"
#include "ArkanoidByWered/UI/Menu/Widgets/Levels/ABWLevelsWidget.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"
#include "Kismet/GameplayStatics.h"

UABWMainMenuWidget::UABWMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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

void UABWMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeGameLogic();
	InitializeLevelsWidget();

	SetActiveColorPalette();
}

void UABWMainMenuWidget::OpenLevels()
{
	if (!LevelsWidget)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMainMenuWidget::OpenLevels|LevelsWidget is nullptr"));
		return;
	}

	LevelsWidget->AddToViewport();
}

void UABWMainMenuWidget::SetCustomization(UImage* PaddleImage, UImage* BallImage)
{
	SetActiveColorPalette();

	SetPaddleColor(PaddleImage);
	SetBallColor(BallImage);
}

void UABWMainMenuWidget::ConfirmCustomization()
{
	UPaperSprite* PaddleSprite = CurrentPalette->PaddlesSprites[PaddleIndex];
	UPaperSprite* BallSprite = CurrentPalette->BallsSprites[BallIndex];

	SaveGameInstance->SetPaddleSprite(PaddleSprite);
	SaveGameInstance->SetBallSprite(BallSprite);

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Slot1"), 0);
}

void UABWMainMenuWidget::ResetIndexes()
{
	PaletteIndex = 0;
	PaddleIndex = 0;
	BallIndex = 2;
}

void UABWMainMenuWidget::NextPaddle()
{
	const int32 PaddlesCount = CurrentPalette->PaddlesSprites.Num();
	CycleArrayIndex(PaddleIndex, PaddlesCount, true);
}

void UABWMainMenuWidget::PreviousPaddle()
{
	const int32 PaddlesCount = CurrentPalette->PaddlesSprites.Num();
	CycleArrayIndex(PaddleIndex, PaddlesCount, false);
}

void UABWMainMenuWidget::NextPalette()
{
	const int32 PalettesCount = Palettes.Num();
	CycleArrayIndex(PaletteIndex, PalettesCount, true);
}

void UABWMainMenuWidget::PreviousPalette()
{
	const int32 PalettesCount = Palettes.Num();
	CycleArrayIndex(PaletteIndex, PalettesCount, false);
}

void UABWMainMenuWidget::InitializeGameLogic()
{
	SaveGameInstance = Cast<UABWCustomizationSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UABWCustomizationSaveGame::StaticClass()));

	const UABWGameInstance* GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	LevelSubsystem = GameInstance->GetSubsystem<UABWLevelSubsystem>();
}

void UABWMainMenuWidget::InitializeLevelsWidget()
{
	if (!LevelsWidgetClass)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWMainMenuWidget::InitializeLevelsWidget|LevelsWidgetClass is nullptr"));
		return;
	}

	LevelsWidget = Cast<UABWLevelsWidget>(CreateWidget(GetWorld(), LevelsWidgetClass));
}

void UABWMainMenuWidget::SetActiveColorPalette()
{
	if (!Palettes.IsValidIndex(PaletteIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWMenuWidget::SetCurrentPalette|PaletteIndex out of bounds!"));
		return;
	}
	CurrentPalette = Palettes[PaletteIndex];
}

void UABWMainMenuWidget::SetPaddleColor(UImage* PaddleImage) const
{
	if (!CurrentPalette->PaddlesSprites.IsValidIndex(PaddleIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWMenuWidget::SetPaddleColor|PaddlesIndex out of bounds!"));
		return;
	}
	UPaperSprite* PaddleSprite = CurrentPalette->PaddlesSprites[PaddleIndex];

	PaddleImage->SetBrushResourceObject(PaddleSprite);
}

void UABWMainMenuWidget::SetBallColor(UImage* BallImage) const
{
	if (!CurrentPalette->BallsSprites.IsValidIndex(BallIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("UABWMenuWidget::SetCustomization|BallIndex out of bounds"));
		return;
	}
	UPaperSprite* BallSprite = CurrentPalette->BallsSprites[BallIndex];

	BallImage->SetBrushResourceObject(BallSprite);
}

void UABWMainMenuWidget::CycleArrayIndex(int32& CurrentIndex, const int32 MaxIndex, const bool bIsIncrement) const
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
