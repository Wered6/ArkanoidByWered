// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ArkanoidByWeredUserSettings.generated.h"

class UDefaultSettingsDataAsset;
class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UArkanoidByWeredUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UArkanoidByWeredUserSettings();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay")
	UPaperSprite* SelectedPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay")
	UPaperSprite* SelectedBall;

	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;

private:
	UPROPERTY()
	UDefaultSettingsDataAsset* DefaultSettingsAsset;
};
