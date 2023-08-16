// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMenuWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "ArkanoidByWeredUserSettings.generated.h"

UCLASS()
class ARKANOIDBYWERED_API UArkanoidByWeredUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay")
	FPaletteSprites SelectedPalette;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay")
	int32 SelectedPaddleShape;

	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;
};
