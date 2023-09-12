// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWBallsAndPaddleSubsystem.h"
#include "ArkanoidByWered/GameplayElements/ABWBall.h"

void UABWBallsAndPaddleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	check(!bInitialized);
	bInitialized = true;
}

void UABWBallsAndPaddleSubsystem::Deinitialize()
{
	check(bInitialized);
	bInitialized = false;
}

void UABWBallsAndPaddleSubsystem::AddBall(AABWBall* Ball)
{
	if (!Ball)
	{
		UE_LOG(LogActor, Warning, TEXT("UABWBallsAndPaddleSubsystem::AddBall|Ball is null"));
		return;
	}
	Balls.Add(Ball);
}

void UABWBallsAndPaddleSubsystem::RemoveBall(AABWBall* Ball)
{
	if (!Ball)
	{
		UE_LOG(LogActor, Warning, TEXT("UABWBallsAndPaddleSubsystem::RemoveBall|Ball is null"));
		return;
	}
	Balls.Remove(Ball);
}
