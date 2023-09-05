// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ABWPaddle.generated.h"

UCLASS()
class ARKANOIDBYWERED_API AABWPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABWPaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetCollisionWidth() const;
	float GetCollisionHeight() const;

	void MoveHorizontal(const float Value);

private:
	void SetDefaultSprite() const;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComp;
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* FloatingPawnMovement;
};
