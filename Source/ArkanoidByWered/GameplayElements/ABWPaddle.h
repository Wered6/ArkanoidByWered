// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ABWPaddle.generated.h"

class UABWUserSettings;
class UFloatingPawnMovement;
class UPaperSpriteComponent;
class UBoxComponent;

UCLASS()
class ARKANOIDBYWERED_API AABWPaddle : public APawn
{
	GENERATED_BODY()

public:
	AABWPaddle();

protected:
	virtual void BeginPlay() override;

public:
	float GetCollisionWidth() const;
	float GetCollisionHeight() const;

	void MoveHorizontal(const float Value);

private:
	void SetDefaultSprite() const;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComp{nullptr};
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComp{nullptr};
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement{nullptr};

	UPROPERTY()
	UABWUserSettings* GameSettings{nullptr};
};
