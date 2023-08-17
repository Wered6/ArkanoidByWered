// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DefaultSettingsDataAsset.generated.h"

class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API UDefaultSettingsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Defaults")
	UPaperSprite* DefaultPaddleSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Defaults")
	UPaperSprite* DefaultBallSprite;
};
