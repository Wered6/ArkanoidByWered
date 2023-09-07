// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ABWUserSettings.generated.h"

class UABWDefaultBallPaddleDA;
class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UABWUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UABWUserSettings();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay")
	UPaperSprite* SelectedPaddle{nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameplay")
	UPaperSprite* SelectedBall{nullptr};

	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;

private:
	UPROPERTY()
	UABWDefaultBallPaddleDA* DefaultSettingsAsset{nullptr};
};
