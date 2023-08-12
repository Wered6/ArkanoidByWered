// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

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

	UFUNCTION(BlueprintCallable, Category="Movement")
	void UpdateVelocityVector(const float X, const float Z);
	UFUNCTION(BlueprintCallable, Category="Movement")
	FVector GetVelocityVector() const;

	float GetWidth() const;

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComp;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float Speed{100.f};
	UPROPERTY(VisibleAnywhere, Category="Movement")
	FVector VelocityVector;
};
