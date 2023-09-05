// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameInstance.h"


bool UABWGameInstance::GetHasPlayerLost() const
{
	return bHasPlayerLost;
}

void UABWGameInstance::SetHasPlayerLost(const bool bPlayerHasLost)
{
	bHasPlayerLost = bPlayerHasLost;
}

bool UABWGameInstance::GetHasPlayerStartGame() const
{
	return bHasPlayerStartGame;
}

void UABWGameInstance::SetHasPlayerStartGame(const bool bPlayerHasStartGame)
{
	bHasPlayerStartGame = bPlayerHasStartGame;
}
