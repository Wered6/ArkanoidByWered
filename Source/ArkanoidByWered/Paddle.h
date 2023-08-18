// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

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

	float GetCollisionWidth() const;

	void AddLive();
	void SubLive();
	int32 GetLives() const;

private:
	void MoveHorizontal(const float Value);

	void SetDefaultSprite() const;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComp;
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* FloatingPawnMovement;

	int32 Lives{3};
};
