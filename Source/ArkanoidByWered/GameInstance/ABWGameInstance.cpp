// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameInstance.h"

bool UABWGameInstance::GetHasPlayerLost() const
{
	return bHasPlayerLost;
}

void UABWGameInstance::SetHasPlayerLost(const bool bPlayerHasLost)
{
	this->bHasPlayerLost = bPlayerHasLost;
}
