// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ABWGameInstance.generated.h"

UCLASS()
class ARKANOIDBYWERED_API UABWGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	bool GetHasPlayerLost() const;
	void SetHasPlayerLost(const bool bHasPlayerLost);
	
private:
	bool bHasPlayerLost{false};
};
