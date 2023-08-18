// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

class UPaperSpriteComponent;

UCLASS()
class ARKANOIDBYWERED_API ABrick : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void HandleOnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category="Sprites")
	TArray<class UPaperSprite*> BrokenBrickSprites;
	UPROPERTY(VisibleAnywhere, Category="Sprites")
	UPaperSpriteComponent* MainSpriteComp;

	int32 NumOfHits{0};
};
