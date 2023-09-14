// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameModeBase.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelSubsystem.h"
#include "ArkanoidByWered/GameInstance/ABWGameInstance.h"
#include "ArkanoidByWered/PlayerControllers/Gameplay/ABWPlayerController.h"
#include "ArkanoidByWered/GameplayElements/Ball/ABWBall.h"
#include "ArkanoidByWered/GameplayElements/Brick/ABWBrick.h"
#include "Kismet/GameplayStatics.h"

void AABWGameModeBase::HandleBallDestruction(AABWBall* Ball)
{
	if (!PlayerController)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::HandleBallDestruction|PlayerController is nullptr"));
		return;
	}

	ReturnBall(Ball);

	const int32 NumberOfActiveBalls = ActiveBalls.Num();

	if (NumberOfActiveBalls <= 0)
	{
		PlayerController->DecrementLife();

		const int32 CurrentLifes = PlayerController->GetLifes();

		if (CurrentLifes <= 0)
		{
			GetWorld()->GetTimerManager().SetTimer(LevelOverTimerHandle, [this]()
			{
				LevelOver(false);
			}, 1.5f, false);
		}
	}
}

void AABWGameModeBase::HandleBrickDestruction()
{
	NumberOfBricks--;
	if (NumberOfBricks <= 0)
	{
		LevelOver(true);
	}
}

AABWBall* AABWGameModeBase::GetBall()
{
	if (InactiveBalls.Num() > 0)
	{
		AABWBall* Ball = InactiveBalls.Pop();

		Ball->Activate();
		ActiveBalls.Add(Ball);
		return Ball;
	}
	return nullptr;
}

void AABWGameModeBase::ReturnBall(AABWBall* Ball)
{
	if (!Ball)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::ReturnBall|Ball is nullptr"));
		return;
	}

	ActiveBalls.Remove(Ball);
	Ball->Deactivate();
	InactiveBalls.Add(Ball);
}

void AABWGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameLogic();
	InitializeBallsPool(64);
}

void AABWGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(LevelOverTimerHandle);
}

void AABWGameModeBase::InitializeGameLogic()
{
	GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	PlayerController = Cast<AABWPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));

	if (!GameInstance)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::InitializeGameLogic|GameInstance is nullptr"));
		return;
	}

	LevelSubsystem = GameInstance->GetSubsystem<UABWLevelSubsystem>();
	GameInstance->SetHasPlayerStartGame(true);

	NumberOfBricks = GetBricksCount();
}

void AABWGameModeBase::InitializeBallsPool(const int32 NumberOfBalls)
{
	if (!BallClass)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::InitializeBallsPool|BallClass is nullptr"));
		return;
	}

	for (int i = 0; i < NumberOfBalls; ++i)
	{
		AABWBall* Ball = GetWorld()->SpawnActor<AABWBall>(BallClass, FVector::ZeroVector, FRotator::ZeroRotator);

		if (!Ball)
		{
			UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::InitializeBallsPool|Ball is nullptr"));
			return;
		}

		InactiveBalls.Add(Ball);
	}
}

void AABWGameModeBase::LevelOver(const bool bWin)
{
	if (!PlayerController)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::LevelOver|PlayerController is nullptr"));
		return;
	}
	if (!GameInstance)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::LevelOver|GameInstance is nullptr"));
		return;
	}
	if (!LevelSubsystem)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::LevelOver|LevelSubsystem is nullptr"));
		return;
	}

	PlayerController->SetPlayerEnabledState(false);
	GameInstance->SetHasPlayerWonLevel(bWin);
	LevelSubsystem->SetCurrentLevelIndex();

	if (bWin)
	{
		LevelSubsystem->CompleteCurrentLevel();
	}

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

int32 AABWGameModeBase::GetBricksCount() const
{
	TArray<AActor*> Bricks;
	UGameplayStatics::GetAllActorsOfClass(this, AABWBrick::StaticClass(), Bricks);
	return Bricks.Num();
}
