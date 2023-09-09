// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ABWCustomizationSaveGame.generated.h"

class UABWDefaultBallPaddleDA;
class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UABWCustomizationSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UABWCustomizationSaveGame();

	void SetBallSprite(UPaperSprite* SelectedBallSprite);
	void SetPaddleSprite(UPaperSprite* SelectedPaddleSprite);
	UPaperSprite* GetBallSprite() const;
	UPaperSprite* GetPaddleSprite() const;

private:
	UPROPERTY()
	UPaperSprite* BallSprite{nullptr};
	UPROPERTY()
	UPaperSprite* PaddleSprite{nullptr};

	UPROPERTY()
	UABWDefaultBallPaddleDA* DefaultBallPaddleDA{nullptr};
};
