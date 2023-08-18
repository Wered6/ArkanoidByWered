// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperFlipbook.h"
#include "HeartsDataAsset.generated.h"


class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UHeartsDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Hearts")
	TArray<UPaperSprite*> HeartsSprites;
	UPROPERTY(EditAnywhere, Category="Flipbook")
	UPaperFlipbook* FillHeart;
	UPROPERTY(EditAnywhere, Category="Flipbook")
	UPaperFlipbook* EmptyHeart;
};
