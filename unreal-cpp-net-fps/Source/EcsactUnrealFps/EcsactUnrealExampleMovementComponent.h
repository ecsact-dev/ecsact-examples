#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EcsactUnrealExampleMovementComponent.generated.h"

UCLASS()

class UEcsactUnrealExampleMovementComponent : public UPawnMovementComponent {
	GENERATED_BODY()
private:
	float MoveDirX;
	float MoveDirY;

public:
	auto SetMoveDirection(float X, float Y) -> void;

	auto IsMoveDirectionSimilar(float X, float Y) const -> bool;

	auto TickComponent(
		float                        DeltaTime,
		enum ELevelTick              TickType,
		FActorComponentTickFunction* ThisTickFunction
	) -> void override;
};