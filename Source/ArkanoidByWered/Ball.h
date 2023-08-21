// Copyright (c) 2023 Wered. All rights reserved.

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
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	float GetCollisionHeight() const;
	
	UFUNCTION(BlueprintCallable)
	void BounceBall(const FVector& HitLocation, const FVector& HitNormal, AActor* HitActor);

private:
	void BounceOffPaddle(const APaddle* Paddle, const FVector& HitLocation);
	void BounceOffWall(const FVector& HitNormal);

	void SetDefaultSprite() const;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComp;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float BallSpeed{0.f};
	FVector InitialVelocityVector{0, 0, 1};
	UPROPERTY(VisibleAnywhere, Category="Movement")
	FVector VelocityVector;
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float Angle{45.f};
};
