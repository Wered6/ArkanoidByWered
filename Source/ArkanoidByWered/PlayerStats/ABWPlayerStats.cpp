// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPlayerStats.h"

UABWPlayerStats::UABWPlayerStats()
{
	CurrentLifes = MaxLifes;
}

void UABWPlayerStats::AddLife()
{
	if (CurrentLifes < MaxLifes)
	{
		++CurrentLifes;
	}
}

void UABWPlayerStats::SubLife()
{
	if (CurrentLifes > MinLifes)
	{
		--CurrentLifes;
	}
}

int32 UABWPlayerStats::GetCurrentLifes() const
{
	return CurrentLifes;
}

int32 UABWPlayerStats::GetMinLifes() const
{
	return MinLifes;
}

int32 UABWPlayerStats::GetMaxLifes() const
{
	return MaxLifes;
}
