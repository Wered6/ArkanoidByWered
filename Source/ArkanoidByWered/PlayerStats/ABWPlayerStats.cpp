// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPlayerStats.h"

UABWPlayerStats::UABWPlayerStats()
{
	Lifes = MaxLifes;
}

void UABWPlayerStats::AddLife()
{
	if (Lifes < MaxLifes)
	{
		++Lifes;
	}
}

void UABWPlayerStats::SubLife()
{
	if (Lifes > MinLifes)
	{
		--Lifes;
	}
}

int32 UABWPlayerStats::GetLife() const
{
	return Lifes;
}
