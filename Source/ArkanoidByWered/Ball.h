// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class APaddle;

UCLASS()
class ARKANOIDBYWERED_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BounceBall(const FVector& HitLocation, const FVector& HitNormal, AActor* HitActor);

private:
	void BounceOffPaddle(const APaddle* Paddle, const FVector& HitLocation);
	void BounceOffWall(const FVector& HitNormal);

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComp;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float BallSpeed{200.f};
	UPROPERTY(VisibleAnywhere, Category="Movement")
	FVector VelocityVector{0, 0, -1};
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float Angle{45.f};
};
