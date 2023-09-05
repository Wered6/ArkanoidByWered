// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABWBall.generated.h"

class AABWGameModeBase;
class AABWPaddle;

UCLASS()
class ARKANOIDBYWERED_API AABWBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AABWBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	float GetCollisionHeight() const;

	void LaunchBall();

	UFUNCTION(BlueprintCallable)
	void BounceBall(const FVector& HitLocation, const FVector& HitNormal, AActor* HitActor);

	bool bIsLaunched{false};

private:
	void BounceOffPaddle(const AABWPaddle* Paddle, const FVector& HitLocation);
	void BounceOffWall(const FVector& HitNormal);

	void SetDefaultSprite() const;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComp;

	FVector InitialVelocityVector{0, 0, 1};
	float InitialBallSpeed{0.f};

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float BallSpeed{200.f};
	UPROPERTY(VisibleAnywhere, Category="Movement")
	FVector VelocityVector;
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float Angle{45.f};

	UPROPERTY()
	AABWGameModeBase* GameMode{nullptr};
};
