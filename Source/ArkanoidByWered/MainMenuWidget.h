// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UPaperSprite;

USTRUCT(BlueprintType)
struct FPaletteSprites
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperSprite*> Paddles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Ball;
};

UCLASS()
class ARKANOIDBYWERED_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPaletteSprites GreenSprites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPaletteSprites GreySprites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPaletteSprites OrangeSprites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPaletteSprites PurpleSprites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPaletteSprites RedSprites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPaletteSprites YellowSprites;
};
