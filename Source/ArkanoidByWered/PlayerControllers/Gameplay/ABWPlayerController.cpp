// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPlayerController.h"
#include "ArkanoidByWered/GameModes/Gameplay/ABWGameModeBase.h"
#include "ArkanoidByWered/GameplayElements/Ball/ABWBall.h"
#include "ArkanoidByWered/UI/HUD/ABWHUDWidget.h"
#include "ArkanoidByWered/GameplayElements/Paddle/ABWPaddle.h"

AABWPlayerController::AABWPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	Lifes = MaxLifes;
}

void AABWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Init();
	check(CheckNullPointers());
	StartGame();
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

void AABWPlayerController::AddLife()
{
	HUD->PlayHeartFillAnimaion(Lifes);

	if (Lifes < MaxLifes)
	{
		Lifes++;
	}
}

void AABWPlayerController::SubLife()
{
	HUD->PlayHeartEmptyAnimaion(Lifes);

	if (Lifes > MinLifes)
	{
		Lifes--;
	}
	if (Lifes > MinLifes)
	{
		SpawnBall();
	}
}

int32 AABWPlayerController::GetLife() const
{
	return Lifes;
}

void AABWPlayerController::Init()
{
	SetHUD();
	SetPaddle();
	SetGameMode();
}

void AABWPlayerController::SetHUD()
{
	if (!HUDWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::SetHUD|HUDWidgetClass is null"));
		return;
	}
	HUD = CreateWidget<UABWHUDWidget>(GetWorld(), HUDWidgetClass);
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

void AABWPlayerController::SetGameMode()
{
	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());
}

bool AABWPlayerController::CheckNullPointers() const
{
	if (!HUD)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWPlayerController::CheckNullPointers|HUD is null"));
		return false;
	}
	if (!Paddle)
	{
		UE_LOG(LogActor, Warning, TEXT("AABWPlayerController::CheckNullPointers|Paddle is null"));
		return false;
	}
	if (!GameMode)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWPlayerController::CheckNullPointers|GameMode is null"));
		return false;
	}
	return true;
}

void AABWPlayerController::StartGame()
{
	HUD->AddToViewport();
	SpawnBall();
}

void AABWPlayerController::MovePaddle(const float Value)
{
	Paddle->MoveHorizontal(Value);
}

void AABWPlayerController::SpawnBall()
{
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
