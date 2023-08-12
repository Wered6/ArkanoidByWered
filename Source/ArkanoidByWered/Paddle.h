// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

class ABall;

UCLASS()
class ARKANOIDBYWERED_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void BounceBall(AActor* OtherActor, const FVector& HitLocation);

private:
	void MoveHorizontal(const float Value);

	float CalculateBounceAngle(const float RelativeHitLocationX, const float BallPaddleHalfWidth) const;
	void UpdateBallVelocity(ABall* Ball, const float BounceAngle, const float Speed) const;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComp;
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* FloatingPawnMovement;
};
