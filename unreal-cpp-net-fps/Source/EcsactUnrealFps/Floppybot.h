#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "GameFramework/Actor.h"
#include "Math/Color.h"
#include "Floppybot.generated.h"

UCLASS(Blueprintable)

class ECSACTUNREALFPS_API AFloppybot : public AActor {
	GENERATED_BODY()

public:
	AFloppybot();

	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitStunned(FExampleFpsStunned Stunned);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateStunned(FExampleFpsStunned Stunned);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoveStunned(FExampleFpsStunned Stunned);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitEnemy(FExampleFpsEnemy Enemy);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateEnemy(FExampleFpsEnemy Enemy);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoveEnemy(FExampleFpsEnemy Enemy);
};
