// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWGameModeBase.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelSubsystem.h"
#include "ArkanoidByWered/GameInstance/ABWGameInstance.h"
#include "ArkanoidByWered/PlayerControllers/ABWPlayerController.h"
#include "ArkanoidByWered/GameplayElements/Ball/ABWBall.h"
#include "ArkanoidByWered/GameplayElements/Brick/ABWBrick.h"
#include "Kismet/GameplayStatics.h"

void AABWGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Init();
	check(CheckNullPointers());
	InitializeBallsPool(64);
	StartGame();
}

void AABWGameModeBase::HandleBallDestruction(AABWBall* Ball)
{
	ReturnBall(Ball);
	const int32 NumberOfActiveBalls = ActiveBalls.Num();
	
	if (NumberOfActiveBalls <= 0)
	{
		PlayerController->SubLife();

		if (PlayerController->GetLife() <= 0)
		{
			FTimerHandle TimerHandle;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
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

void AABWGameModeBase::Init()
{
	GameInstance = Cast<UABWGameInstance>(GetGameInstance());
	LevelSubsystem = GameInstance->GetSubsystem<UABWLevelSubsystem>();
	PlayerController = Cast<AABWPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0));
}

void AABWGameModeBase::StartGame()
{
	NumberOfBricks = GetBricksCount();

	GameInstance->SetHasPlayerStartGame(true);
}

bool AABWGameModeBase::CheckNullPointers() const
{
	if (!GameInstance)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::CheckNullPointers|GameInstance is null"));
		return false;
	}
	if (!LevelSubsystem)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::CheckNullPointers|LevelSubsystem is null"));
		return false;
	}
	if (!PlayerController)
	{
		UE_LOG(LogGameMode, Warning, TEXT("AABWGameModeBase::CheckNullPointers|PlayerController is null"));
		return false;
	}
	return true;
}

void AABWGameModeBase::LevelOver(const bool bWin) const
{
	PlayerController->SetPlayerEnabledState(false);
	GameInstance->SetHasPlayerWonLevel(bWin);

	if (bWin)
	{
		LevelSubsystem->SetCurrentLevelIndex();
		LevelSubsystem->CompleteCurrentLevel();
	}

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

int32 AABWGameModeBase::GetBallsCount() const
{
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsOfClass(this, AABWBall::StaticClass(), Balls);
	return Balls.Num();
}

int32 AABWGameModeBase::GetBricksCount() const
{
	TArray<AActor*> Bricks;
	UGameplayStatics::GetAllActorsOfClass(this, AABWBrick::StaticClass(), Bricks);
	return Bricks.Num();
}

void AABWGameModeBase::InitializeBallsPool(const int32 NumberOfBalls)
{
	for (int i = 0; i < NumberOfBalls; ++i)
	{
		AABWBall* Ball = GetWorld()->SpawnActor<AABWBall>(BallClass, FVector::ZeroVector, FRotator::ZeroRotator);
		InactiveBalls.Add(Ball);
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
	ActiveBalls.Remove(Ball);
	Ball->Deactivate();
	InactiveBalls.Add(Ball);
}
