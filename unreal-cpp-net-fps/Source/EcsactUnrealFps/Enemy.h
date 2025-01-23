#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS(Blueprintable)

class ECSACTUNREALFPS_API AEnemy : public AActor {
	GENERATED_BODY()

public:
	AEnemy();

	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitStunned(FExampleFpsStunned Stunned);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateStunned(FExampleFpsStunned Stunned);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoveStunned(FExampleFpsStunned Stunned);
};
