// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABWEndGameWidget.generated.h"

class UABWMainMenuWidget;

UCLASS()
class ARKANOIDBYWERED_API UABWEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="UI|Menu")
	void OpenMenu() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="UI|Menu")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY()
	UABWMainMenuWidget* MenuWidget{nullptr};
};
