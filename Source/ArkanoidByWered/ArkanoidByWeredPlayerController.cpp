// Copyright (c) 2023 Wered. All rights reserved.


#include "ArkanoidByWeredPlayerController.h"
#include "Ball.h"
#include "HUDWidget.h"
#include "Paddle.h"
#include "Kismet/GameplayStatics.h"


AArkanoidByWeredPlayerController::AArkanoidByWeredPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AArkanoidByWeredPlayerController::AddLife()
{
	if (Lifes < 3)
	{
		Lifes++;
	}
}

void AArkanoidByWeredPlayerController::SubLife()
{
	UWidgetAnimation* Animation1 = HUD->HeartAnimation1;
	UWidgetAnimation* Animation2 = HUD->HeartAnimation2;
	UWidgetAnimation* Animation3 = HUD->HeartAnimation3;

	if (Animation1 && Animation2 && Animation3)
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
	SpawnBall();
}

void AArkanoidByWeredPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetPaddle();
	SpawnBall();
	if (HUDWidgetClass)
	{
		HUD = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		if (HUD)
		{
			HUD->AddToViewport();
		}
	}
}

void AArkanoidByWeredPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnedBall && !SpawnedBall->bIsLaunched)
	{
		UpdateIdleBallPosition();
	}
	else
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}

void AArkanoidByWeredPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MovePaddleHorizontal"), this, &AArkanoidByWeredPlayerController::MovePaddle);
	InputComponent->BindAction(TEXT("LaunchBall"), IE_Pressed, this, &AArkanoidByWeredPlayerController::LaunchBall);
}

int32 AArkanoidByWeredPlayerController::GetBallsCount() const
{
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsOfClass(this, ABall::StaticClass(), Balls);
	return Balls.Num();
}

void AArkanoidByWeredPlayerController::SetPaddle()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		Paddle = Cast<APaddle>(ControlledPawn);
	}
}

void AArkanoidByWeredPlayerController::MovePaddle(const float Value)
{
	if (Paddle)
	{
		Paddle->MoveHorizontal(Value);
	}
}

void AArkanoidByWeredPlayerController::SpawnBall()
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

void AArkanoidByWeredPlayerController::LaunchBall()
{
	if (SpawnedBall)
	{
		SpawnedBall->LaunchBall();
	}
}

void AArkanoidByWeredPlayerController::UpdateIdleBallPosition() const
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
