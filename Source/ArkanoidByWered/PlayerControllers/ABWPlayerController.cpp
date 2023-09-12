// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPlayerController.h"
#include "ArkanoidByWered/GameModes/ABWGameModeBase.h"
#include "ArkanoidByWered/GameplayElements/ABWBall.h"
#include "ArkanoidByWered/UI/HUD/ABWHUDWidget.h"
#include "ArkanoidByWered/GameplayElements/ABWPaddle.h"

AABWPlayerController::AABWPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AABWPlayerController::AddLife()
{
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::AddLife|HUD is null"));
		return;
	}

	HUD->PlayHeartEmptyAnimaion(Lifes);

	if (Lifes < 3)
	{
		Lifes++;
	}
}

void AABWPlayerController::SubLife()
{
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::SubLife|HUD is null"));
		return;
	}

	HUD->PlayHeartEmptyAnimaion(Lifes);

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
	SetHUD();
	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());
	SpawnBall();
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

	SpawnedBall = GameMode->GetBall();
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
