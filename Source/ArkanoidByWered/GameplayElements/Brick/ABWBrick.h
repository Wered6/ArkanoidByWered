// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABWBrick.generated.h"

class AABWGameModeBase;
class UPaperSpriteComponent;
class UPaperSprite;

UCLASS()
class ARKANOIDBYWERED_API AABWBrick : public AActor
{
	GENERATED_BODY()

public:
	AABWBrick();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HandleOnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category="Sprites")
	TArray<UPaperSprite*> BrokenBrickSprites;
	UPROPERTY(VisibleAnywhere, Category="Sprites")
	UPaperSpriteComponent* SpriteComp{nullptr};

	int32 NumOfHits{0};

	UPROPERTY()
	AABWGameModeBase* GameMode{nullptr};
};
