// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPlayerController.h"
#include "ArkanoidByWered/GameplayElements/ABWBall.h"
#include "ArkanoidByWered/UI/HUD/ABWHUDWidget.h"
#include "ArkanoidByWered/GameplayElements/ABWPaddle.h"

AABWPlayerController::AABWPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AABWPlayerController::AddLife()
{
	HeartAnimation(false);

	if (Lifes < 3)
	{
		Lifes++;
	}
}

void AABWPlayerController::SubLife()
{
	HeartAnimation(true);

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
	if (!HUDWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::SetHUD|HUDWidgetClass is null"));
		return;
	}

	HUD = CreateWidget<UABWHUDWidget>(GetWorld(), HUDWidgetClass);

	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::SetHUD|HUD is null"));
		return;
	}

	HUD->AddToViewport();
	Animation1 = HUD->HeartAnimation1;
	Animation2 = HUD->HeartAnimation2;
	Animation3 = HUD->HeartAnimation3;
}

void AABWPlayerController::HeartAnimation(const bool bReverse) const
{
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::HeartAnimation|HUD is null"));
		return;
	}
	if (!Animation1)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::HeartAnimation|Animation1 is null"));
		return;
	}
	if (!Animation2)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::HeartAnimation|Animation2 is null"));
		return;
	}
	if (!Animation3)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::HeartAnimation|Animation3 is null"));
		return;
	}

	if (!bReverse)
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
	else
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
}

void AABWPlayerController::SetPaddle()
{
	APawn* ControlledPawn = GetPawn();

	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::SetPaddle|ControlledPawn is null"));
		return;
	}

	Paddle = Cast<AABWPaddle>(ControlledPawn);
}

void AABWPlayerController::MovePaddle(const float Value)
{
	if (!Paddle)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::MovePaddle|Paddle is null"));
		return;
	}

	Paddle->MoveHorizontal(Value);
}

void AABWPlayerController::SpawnBall()
{
	if (!BallClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::SpawnBall|BallClass is null"));
		return;
	}

	SpawnedBall = GetWorld()->SpawnActor<AABWBall>(BallClass, FVector::ZeroVector, FRotator::ZeroRotator);
	UpdateIdleBallPosition();
}

void AABWPlayerController::LaunchBall()
{
	if (!SpawnedBall)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::LaunchBall|SpawnedBall is null"));
		return;
	}

	SpawnedBall->LaunchBall();
}

void AABWPlayerController::UpdateIdleBallPosition() const
{
	if (!Paddle)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::UpdateIdleBallPosition|Paddle is null"));
		return;
	}
	if (!SpawnedBall)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::UpdateIdleBallPosition|SpawnedBall is null"));
		return;
	}

	FVector BallStartPosition = Paddle->GetActorLocation();
	constexpr float BallToPaddleOffset{0.01f};
	BallStartPosition.Z = BallStartPosition.Z
		+ Paddle->GetCollisionHeight() / 2
		+ SpawnedBall->GetCollisionHeight() / 2
		+ BallToPaddleOffset;

	SpawnedBall->SetActorLocation(BallStartPosition);
}
