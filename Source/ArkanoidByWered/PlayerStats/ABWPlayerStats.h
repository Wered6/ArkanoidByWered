// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
// #include "UObject/NoExportTypes.h"
#include "ABWPlayerStats.generated.h"

UCLASS()
class ARKANOIDBYWERED_API UABWPlayerStats : public UObject
{
	GENERATED_BODY()

public:
	UABWPlayerStats();

	void AddLife();
	void SubLife();
	int32 GetLife() const;

private:
	const int32 MaxLifes{3};
	const int32 MinLifes{0};
	int32 Lifes;
};
