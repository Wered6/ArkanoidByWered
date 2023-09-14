// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPlayerController.h"
#include "ArkanoidByWered/GameModes/Gameplay/ABWGameModeBase.h"
#include "ArkanoidByWered/GameplayElements/Ball/ABWBall.h"
#include "ArkanoidByWered/GameplayElements/Paddle/ABWPaddle.h"
#include "ArkanoidByWered/PlayerStats/ABWPlayerStats.h"
#include "ArkanoidByWered/UI/HUD/ABWHUD.h"

AABWPlayerController::AABWPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AABWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitializeHUD();
	InitializeGameplayElements();
	InitializeGameLogic();

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

void AABWPlayerController::IncrementLife()
{
	if (!PlayerStats)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::IncrementLife|PlayersStats is nullptr"));
		return;
	}
	if (!HUD)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::IncrementLife|HUD is nullptr"));
		return;
	}

	const int32 CurrentLifes = PlayerStats->GetCurrentLifes();

	HUD->PlayHeartAnimation(CurrentLifes, true);
	PlayerStats->AddLife();
}

void AABWPlayerController::DecrementLife()
{
	if (!PlayerStats)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::DecrementLife|PlayerStats is nullptr"));
		return;
	}
	if (!HUD)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::DecrementLife|HUD is nullptr"));
		return;
	}

	const int32 MinLifes = PlayerStats->GetMinLifes();

	HUD->PlayHeartAnimation(PlayerStats->GetCurrentLifes(), false);
	PlayerStats->SubLife();
	if (PlayerStats->GetCurrentLifes() > MinLifes)
	{
		SpawnBall();
	}
}

int32 AABWPlayerController::GetLife() const
{
	if (!PlayerStats)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::GetLife|PlayerStats is nullptr"));
		return -1;
	}

	return PlayerStats->GetCurrentLifes();
}

void AABWPlayerController::InitializeGameLogic()
{
	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());
	PlayerStats = NewObject<UABWPlayerStats>();
}

void AABWPlayerController::InitializeGameplayElements()
{
	APawn* ControlledPawn = GetPawn();

	if (!ControlledPawn)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("AABWPlayerController::InitializeGameplayElements|ControlledPawn is nullptr"));
		return;
	}

	Paddle = Cast<AABWPaddle>(ControlledPawn);
}

void AABWPlayerController::InitializeHUD()
{
	HUD = Cast<AABWHUD>(GetHUD());
}

void AABWPlayerController::StartGame()
{
	if (!HUD)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::StartGame|HUD is nullptr"));
		return;
	}

	HUD->AddToViewport();
	SpawnBall();
}

void AABWPlayerController::MovePaddle(const float Value)
{
	if (!Paddle)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::MovePaddle|Paddle is nullptr"));
		return;
	}

	Paddle->MoveHorizontal(Value);
}

void AABWPlayerController::SpawnBall()
{
	if (!GameMode)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::SpawnBall|GameMode is nullptr"));
		return;
	}

	SpawnedBall = GameMode->GetBall();
	UpdateIdleBallPosition();
}

void AABWPlayerController::LaunchBall()
{
	if (!SpawnedBall)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::LaunchBall|SpawnedBall is nullptr"));
		return;
	}

	SpawnedBall->LaunchBall();
}

void AABWPlayerController::UpdateIdleBallPosition() const
{
	if (!Paddle)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::UpdateIdleBallPosition|Paddle is nullptr"));
		return;
	}
	if (!SpawnedBall)
	{
		UE_LOG(LogPlayerController, Warning,
		       TEXT("AABWPlayerController::UpdateIdleBallPosition|SpawnedBall is nullptr"));
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

// todo PlayerState for PlayerStats and HUD in PlayerController
