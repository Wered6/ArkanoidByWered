// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWered/UI/Menu/Widgets/Levels/ABWLevelsWidget.h"
#include "ArkanoidByWered/GameInstance/ABWGameInstance.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelData.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelSubsystem.h"
#include "ArkanoidByWered/UI/Menu/Widgets/MainMenu/ABWMainMenuWidget.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"
#include "Components/Button.h"

void UABWLevelsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeGameLogic();
	UpdateLevelsButtonsStates();
}

void UABWLevelsWidget::InitializeGameLogic()
{
	const UABWGameInstance* GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	LevelSubsystem = GameInstance->GetSubsystem<UABWLevelSubsystem>();
}

void UABWLevelsWidget::UpdateLevelsButtonsStates()
{
	if (!LevelSubsystem)
	{
		UE_LOG(LogMenu, Warning, TEXT("UABWLevelsWidget::UpdateLevelsButtonsStates|LevelSubsystem is nullptr"));
		return;
	}

	const TArray<UABWLevelData*> LevelsData = LevelSubsystem->GetLevelsDataArray();

	for (int i = 0; i < LevelsData.Num(); ++i)
	{
		const FName LevelName = LevelsData[i]->GetLevelName();
		const FName LevelButtonName = FName(FString::Printf(TEXT("Levels%sBUtton"), *LevelName.ToString()));
		const bool bIsLevelUnlocked = LevelsData[i]->GetIsLevelUnlocked();

		UButton* LevelButton = Cast<UButton>(GetWidgetFromName(LevelButtonName));
		LevelButton->SetIsEnabled(bIsLevelUnlocked);
	}
}
