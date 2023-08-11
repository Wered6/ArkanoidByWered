// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = CollisionComp;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->SetupAttachment(CollisionComp);

	// Initial CurrentVelocity
	VelocityVector = {0, 0, -InitialVelocity};
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set the ball in motion, taking delta time into account and enable collision
	const FVector Movement = VelocityVector * DeltaTime;
	AddActorLocalOffset(Movement, true);
}

void ABall::UpdateVelocityVector(const float X, const float Z)
{
	VelocityVector = {X, 0, Z};
}

FVector ABall::GetVelocityVector() const
{
	return VelocityVector;
}

void ABall::SetHitLocationRelativeToPaddle(const FVector& HitLocation)
{
	HitLocationRelativeToPaddle = HitLocation;
}

FVector ABall::GetHitLocationRelativeToPaddle() const
{
	return HitLocationRelativeToPaddle;
}

float ABall::GetWidth() const
{
	return CollisionComp->GetUnscaledBoxExtent().X * 2.f;
}
