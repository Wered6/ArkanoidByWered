// Copyright (c) 2023 Wered. All rights reserved.


#include "MainMenuWidget.h"
#include "ArkanoidByWered/Settings/ABWUserSettings.h"
#include "ArkanoidByWered/DataAssets/BallPaddleDA.h"
#include "Components/Image.h"
#include "PaperSprite.h"
#include "ArkanoidByWered/Core/LevelSystem/ABWLevelSubsystem.h"
#include "ArkanoidByWered/GameInstance/ABWGameInstance.h"
#include "Components/Button.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBallPaddleDA> GreenAssetFinder(
		TEXT("/Script/ArkanoidByWered.BallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/GreenDA.GreenDA'"));
	static ConstructorHelpers::FObjectFinder<UBallPaddleDA> GreyAssetFinder(
		TEXT("/Script/ArkanoidByWered.BallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/GreyDa.GreyDa'"));
	static ConstructorHelpers::FObjectFinder<UBallPaddleDA> OrangeAssetFinder(
		TEXT("/Script/ArkanoidByWered.BallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/OrangeDA.OrangeDA'"));
	static ConstructorHelpers::FObjectFinder<UBallPaddleDA> PurpleAssetFinder(
		TEXT("/Script/ArkanoidByWered.BallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/PurpleDA.PurpleDA'"));
	static ConstructorHelpers::FObjectFinder<UBallPaddleDA> RedAssetFinder(
		TEXT("/Script/ArkanoidByWered.BallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/RedDA.RedDA'"));
	static ConstructorHelpers::FObjectFinder<UBallPaddleDA> YellowAssetFinder(
		TEXT("/Script/ArkanoidByWered.BallPaddleDA'/Game/Assets/DataAssets/PaddlesAndBalls/YellowDA.YellowDA'"));

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

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const UABWGameInstance* GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	LevelSubsystem = GameInstance->GetSubsystem<UABWLevelSubsystem>();

	SetLevelButtons();
	SetLevelButtonsAvailability();
}

void UMainMenuWidget::SetCustomization(UImage* PaddleImage, UImage* BallImage)
{
	const UBallPaddleDA* CurrentPalette = GetCurrentPalette();
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
	const UBallPaddleDA* CurrentPalette = GetCurrentPalette();
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
	const UBallPaddleDA* CurrentPalette = GetCurrentPalette();
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

void UMainMenuWidget::SetLevelButtons()
{
	Level1Button = Cast<UButton>(GetWidgetFromName("LevelsLevel1Button"));
	Level2Button = Cast<UButton>(GetWidgetFromName("LevelsLevel2Button"));
	Level3Button = Cast<UButton>(GetWidgetFromName("LevelsLevel3Button"));
}

void UMainMenuWidget::SetLevelButtonsAvailability() const
{
	TArray<FLevelData*> LevelsData = LevelSubsystem->GetLevelsDataArray();

	const bool* bIsLevel1Unlocked = &LevelsData[0]->bIsLevelUnlocked;
	const bool* bIsLevel2Unlocked = &LevelsData[1]->bIsLevelUnlocked;
	const bool* bIsLevel3Unlocked = &LevelsData[2]->bIsLevelUnlocked;

	if (Level1Button)
	{
		Level1Button->SetIsEnabled(*bIsLevel1Unlocked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level1Button is null"));
	}
	if (Level2Button)
	{
		Level2Button->SetIsEnabled(*bIsLevel2Unlocked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level2Button is null"));
	}
	if (Level3Button)
	{
		Level3Button->SetIsEnabled(*bIsLevel3Unlocked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level3Button is null"));
	}
}

const UBallPaddleDA* UMainMenuWidget::GetCurrentPalette()
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
