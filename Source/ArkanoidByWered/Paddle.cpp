// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APaddle::APaddle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->SetupAttachment(CollisionComp);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &APaddle::MoveHorizontal);
}

void APaddle::SetBall(ABall* BouncedBall)
{
	Ball = BouncedBall;
}

ABall* APaddle::GetBall() const
{
	return Ball;
}

void APaddle::BounceTheBall() const
{
	const float WholeCollision = CollisionComp->GetUnscaledBoxExtent().X + Ball->GetWidth() / 2;
	Ball->SetAngle(Ball->GetHitLocationRelativeToPaddle().X / WholeCollision);
	
	const float Radians = FMath::DegreesToRadians(90 - Ball->GetAngle() * 45);
	const float XValue = Ball->GetVelocityVector().Size() * FMath::Cos(Radians);
	const float ZValue = Ball->GetVelocityVector().Size() * FMath::Sin(Radians);

	Ball->UpdateVelocityVector(XValue, ZValue);
}

void APaddle::MoveHorizontal(const float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}
