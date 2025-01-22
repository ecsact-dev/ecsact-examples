// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushExplosionVFX.generated.h"

UCLASS(Blueprintable)

class ECSACTUNREALFPS_API APushExplosionVFX : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APushExplosionVFX();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float BaseMultiplier = 30.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float ForceChargeMultiplier;
};
