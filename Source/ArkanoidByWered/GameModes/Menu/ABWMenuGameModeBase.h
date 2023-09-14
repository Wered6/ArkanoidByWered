// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABWMenuGameModeBase.generated.h"

class UABWGameInstance;
class UABWMenu;

UCLASS()
class ARKANOIDBYWERED_API AABWMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void Init();

	void OpenAppropriateWidget() const;

	UPROPERTY(EditDefaultsOnly, Category="Menu")
	TSubclassOf<UABWMenu> MenuClass;
	UPROPERTY()
	UABWMenu* Menu{nullptr};

	UPROPERTY()
	UABWGameInstance* GameInstance{nullptr};
};
