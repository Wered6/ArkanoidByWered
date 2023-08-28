// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameModeBase.h"
#include "ABWPlayerController.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Kismet/GameplayStatics.h"

void AABWGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	StartGame();
}

void AABWGameModeBase::StartGame()
{
	BallsCount = GetBallsCount();
	BricksCount = GetBricksCount();
	Paddle = Cast<APaddle>(UGameplayStatics::GetPlayerPawn(this, 0));
	ABWPlayerController = Cast<AABWPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));
}

int32 AABWGameModeBase::GetBallsCount() const
{
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsOfClass(this, ABall::StaticClass(), Balls);
	return Balls.Num();
}

int32 AABWGameModeBase::GetBricksCount() const
{
	TArray<AActor*> Bricks;
	UGameplayStatics::GetAllActorsOfClass(this, ABrick::StaticClass(), Bricks);
	return Bricks.Num();
}
