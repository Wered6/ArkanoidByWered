// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperFlipbook.h"
#include "ABWHeartsDA.generated.h"


class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UABWHeartsDA : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Hearts")
	TArray<UPaperSprite*> HeartsSprites;
};
