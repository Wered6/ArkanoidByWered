// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABWBall.generated.h"

class UABWCustomizationSaveGame;
class AABWGameModeBase;
class UPaperSpriteComponent;
class UBoxComponent;
class AABWPaddle;

UCLASS()
class ARKANOIDBYWERED_API AABWBall : public AActor
{
	GENERATED_BODY()

public:
	AABWBall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void Activate();
	void Deactivate();

	float GetCollisionHeight() const;

	void LaunchBall();

	UFUNCTION(BlueprintCallable)
	void BounceBall(const FVector& HitLocation, const FVector& HitNormal, AActor* HitActor);

	bool bIsLaunched{false};

private:
	void BounceOffPaddle(const AABWPaddle* Paddle, const FVector& HitLocation);
	void BounceOffWall(const FVector& HitNormal);

	void Init();
	void SetDefaultSprite() const;
	bool CheckNullPointers() const;

	FVector InitialVelocityVector{0, 0, 1};
	float InitialBallSpeed{0.f};

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float BallSpeed{200.f};
	UPROPERTY(VisibleAnywhere, Category="Movement")
	FVector VelocityVector{FVector::ZeroVector};
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float Angle{45.f};

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComp{nullptr};
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComp{nullptr};

	UPROPERTY()
	AABWGameModeBase* GameMode{nullptr};
	UPROPERTY()
	UABWCustomizationSaveGame* LoadGameInstance{nullptr};
};
