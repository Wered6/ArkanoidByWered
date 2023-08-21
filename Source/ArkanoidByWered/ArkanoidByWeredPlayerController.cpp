// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWeredPlayerController.h"
#include "Ball.h"
#include "HUDWidget.h"
#include "Paddle.h"


AArkanoidByWeredPlayerController::AArkanoidByWeredPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AArkanoidByWeredPlayerController::AddLive()
{
	if (Lives < 3)
	{
		Lives++;
	}
}

void AArkanoidByWeredPlayerController::SubLive()
{
	UWidgetAnimation* Animation1 = HUD->HeartAnimation1;
	UWidgetAnimation* Animation2 = HUD->HeartAnimation2;
	UWidgetAnimation* Animation3 = HUD->HeartAnimation3;

	if (Animation1 && Animation2 && Animation3)
	{
		switch (Lives)
		{
		case 3:
			HUD->PlayAnimation(Animation3);
			break;
		case 2:
			HUD->PlayAnimation(Animation2);
			break;
		case 1:
			HUD->PlayAnimation(Animation1);
			break;
		default:
			break;
		}
	}
	if (Lives > 0)
	{
		Lives--;
	}
	SpawnBall();
}

void AArkanoidByWeredPlayerController::SpawnBall()
{
	if (BallClass)
	{
		const FVector BallSpawnLocation = FVector(240, 0, -220);
		const FRotator BallSpawnRotation = FRotator::ZeroRotator;

		SpawnedBall = GetWorld()->SpawnActor<ABall>(BallClass, BallSpawnLocation, BallSpawnRotation);
	}
}

void AArkanoidByWeredPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetPaddle();

	if (HUDWidgetClass)
	{
		HUD = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		if (HUD)
		{
			HUD->AddToViewport();
		}
	}
	SpawnBall();
}

void AArkanoidByWeredPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnedBall && Paddle)
	{
		constexpr float Offset{0.01f};
		FVector NewBallPosition = Paddle->GetActorLocation();
		NewBallPosition.Z = NewBallPosition.Z + Paddle->GetCollisionHeight() / 2;
		NewBallPosition.Z = NewBallPosition.Z + SpawnedBall->GetCollisionHeight() / 2;
		NewBallPosition.Z = NewBallPosition.Z + Offset;
		
		SpawnedBall->SetActorLocation(NewBallPosition);
	}
}

void AArkanoidByWeredPlayerController::SetPaddle()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		Paddle = Cast<APaddle>(ControlledPawn);
	}
}
