// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWPlayerController.h"
#include "ArkanoidByWered/GameModes/Gameplay/ABWGameModeBase.h"
#include "ArkanoidByWered/GameplayElements/Ball/ABWBall.h"
#include "ArkanoidByWered/UI/HUD/ABWHUDHearts.h"
#include "ArkanoidByWered/GameplayElements/Paddle/ABWPaddle.h"
#include "ArkanoidByWered/PlayerStats/ABWPlayerStats.h"

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
	if (PlayerStats)
	{
		const int32 CurrentLifes = PlayerStats->GetCurrentLifes();
		if (HUD)
		{
			HUD->PlayHeartFillAnimaion(CurrentLifes);
			PlayerStats->AddLife();
		}
		else
		{
			UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::IncrementLife|HUD is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::IncrementLife|PlayerStats is nullptr"));
	}
}

void AABWPlayerController::DecrementLife()
{
	if (PlayerStats)
	{
		const int32 MinLifes = PlayerStats->GetMinLifes();
		if (HUD)
		{
			HUD->PlayHeartEmptyAnimaion(PlayerStats->GetCurrentLifes());
			PlayerStats->SubLife();
			if (PlayerStats->GetCurrentLifes() > MinLifes)
			{
				SpawnBall();
			}
		}
		else
		{
			UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::DecrementLife|HUD is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::DecrementLife|PlayerStats is nullptr"));
	}
}

int32 AABWPlayerController::GetLife() const
{
	if (PlayerStats)
	{
		return PlayerStats->GetCurrentLifes();
	}
	UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::GetLife|PlayerStats is nullptr"));
	return -1;
}

void AABWPlayerController::InitializeGameLogic()
{
	GameMode = Cast<AABWGameModeBase>(GetWorld()->GetAuthGameMode());
	PlayerStats = NewObject<UABWPlayerStats>();
}

void AABWPlayerController::InitializeGameplayElements()
{
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn)
	{
		Paddle = Cast<AABWPaddle>(ControlledPawn);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::SetPaddle|ControlledPawn is nullptr"));
	}
}

void AABWPlayerController::InitializeHUD()
{
	if (HUDWidgetClass)
	{
		HUD = CreateWidget<UABWHUDHearts>(GetWorld(), HUDWidgetClass);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AABWPlayerController::SetHUD|HUDWidgetClass is null"));
	}
}

void AABWPlayerController::StartGame()
{
	if (HUD)
	{
		HUD->AddToViewport();
	}
	else
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::StartGame|HUD is nullptr"));
	}

	SpawnBall();
}

void AABWPlayerController::MovePaddle(const float Value)
{
	if (Paddle)
	{
		Paddle->MoveHorizontal(Value);
	}
	else
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::MovePaddle|Paddle is nullptr"));
	}
}

void AABWPlayerController::SpawnBall()
{
	if (GameMode)
	{
		SpawnedBall = GameMode->GetBall();
	}
	else
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::SpawnBall|GameMode is nullptr"));
	}

	UpdateIdleBallPosition();
}

void AABWPlayerController::LaunchBall()
{
	if (SpawnedBall)
	{
		SpawnedBall->LaunchBall();
	}
	else
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::LaunchBall|SpawnedBall is nullptr"));
	}
}

void AABWPlayerController::UpdateIdleBallPosition() const
{
	if (Paddle)
	{
		FVector BallStartPosition = Paddle->GetActorLocation();
		if (SpawnedBall)
		{
			constexpr float BallToPaddleOffset{0.01f};
			BallStartPosition.Z = BallStartPosition.Z
				+ Paddle->GetCollisionHeight() / 2
				+ SpawnedBall->GetCollisionHeight() / 2
				+ BallToPaddleOffset;

			SpawnedBall->SetActorLocation(BallStartPosition);
		}
		else
		{
			UE_LOG(LogPlayerController, Warning,
			       TEXT("AABWPlayerController::UpdateIdleBallPosition|SpawnedBall is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogPlayerController, Warning, TEXT("AABWPlayerController::UpdateIdleBallPosition|Paddle is nullptr"));
	}
}

// todo PlayerState for PlayerStats and HUD in PlayerController
