// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPlayerController.h"
#include "Ball.h"
#include "HUDWidget.h"
#include "Paddle.h"

AABWPlayerController::AABWPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AABWPlayerController::AddLife()
{
	if (HUD && Animation1 && Animation2 && Animation3)
	{
		switch (Lifes)
		{
		case 1:
			HUD->PlayAnimation(Animation2, 0, 1, EUMGSequencePlayMode::Reverse);
		case 2:
			HUD->PlayAnimation(Animation3, 0, 1, EUMGSequencePlayMode::Reverse);
		default:
			break;
		}
	}
	if (Lifes < 3)
	{
		Lifes++;
	}
}

void AABWPlayerController::SubLife()
{
	if (HUD && Animation1 && Animation2 && Animation3)
	{
		switch (Lifes)
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
	if (Lifes > 0)
	{
		Lifes--;
	}
	if (Lifes > 0)
	{
		SpawnBall();
	}
}

int32 AABWPlayerController::GetLife() const
{
	return Lifes;
}

void AABWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetPaddle();
	SpawnBall();
	SetHUD();
}

void AABWPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnedBall && !SpawnedBall->bIsLaunched)
	{
		UpdateIdleBallPosition();
	}
}

void AABWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MovePaddleHorizontal"), this, &AABWPlayerController::MovePaddle);
	InputComponent->BindAction(TEXT("LaunchBall"), IE_Pressed, this, &AABWPlayerController::LaunchBall);
}

void AABWPlayerController::SetPlayerEnabledState(const bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
}

void AABWPlayerController::SetHUD()
{
	if (HUDWidgetClass)
	{
		HUD = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		if (HUD)
		{
			HUD->AddToViewport();
		}
	}

	Animation1 = HUD->HeartAnimation1;
	Animation2 = HUD->HeartAnimation2;
	Animation3 = HUD->HeartAnimation3;
}

void AABWPlayerController::SetPaddle()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		Paddle = Cast<APaddle>(ControlledPawn);
	}
}

void AABWPlayerController::MovePaddle(const float Value)
{
	if (Paddle)
	{
		Paddle->MoveHorizontal(Value);
	}
}

void AABWPlayerController::SpawnBall()
{
	if (BallClass)
	{
		SpawnedBall = GetWorld()->SpawnActor<ABall>(BallClass, FVector::ZeroVector, FRotator::ZeroRotator);
		UpdateIdleBallPosition();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ball Class is not set!"));
	}
}

void AABWPlayerController::LaunchBall()
{
	if (SpawnedBall)
	{
		SpawnedBall->LaunchBall();
	}
}

void AABWPlayerController::UpdateIdleBallPosition() const
{
	if (Paddle && SpawnedBall)
	{
		FVector BallStartPosition = Paddle->GetActorLocation();
		constexpr float BallToPaddleOffset{0.01f};
		BallStartPosition.Z = BallStartPosition.Z
			+ Paddle->GetCollisionHeight() / 2
			+ SpawnedBall->GetCollisionHeight() / 2
			+ BallToPaddleOffset;
		SpawnedBall->SetActorLocation(BallStartPosition);
	}
}
