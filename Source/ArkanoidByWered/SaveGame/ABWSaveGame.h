// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ABWSaveGame.generated.h"

class UABWDefaultBallPaddleDA;
class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UABWSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UABWSaveGame();
	
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
