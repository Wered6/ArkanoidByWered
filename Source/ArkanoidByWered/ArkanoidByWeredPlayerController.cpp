// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWeredPlayerController.h"


void AArkanoidByWeredPlayerController::AddLive()
{
	if (Lives < 3)
	{
		Lives++;
	}
}

void AArkanoidByWeredPlayerController::SubLive()
{
	if (Lives > 0)
	{
		Lives--;
	}
}

int32 AArkanoidByWeredPlayerController::GetLives() const
{
	return Lives;
}

void AArkanoidByWeredPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
