// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ABWPlayerStats.generated.h"

UCLASS()
class ARKANOIDBYWERED_API UABWPlayerStats : public UObject
{
	GENERATED_BODY()

public:
	UABWPlayerStats();

	void AddLife();
	void SubLife();

	int32 GetCurrentLifes() const;
	int32 GetMinLifes() const;
	int32 GetMaxLifes() const;

private:
	int32 CurrentLifes;
	const int32 MinLifes{0};
	const int32 MaxLifes{3};
};
