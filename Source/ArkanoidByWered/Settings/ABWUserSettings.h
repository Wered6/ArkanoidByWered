// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ABWUserSettings.generated.h"

class UDefaultBallPaddleDA;
class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UABWUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UABWUserSettings();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay")
	UPaperSprite* SelectedPaddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay")
	UPaperSprite* SelectedBall;

	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;

private:
	UPROPERTY()
	UDefaultBallPaddleDA* DefaultSettingsAsset;
};
