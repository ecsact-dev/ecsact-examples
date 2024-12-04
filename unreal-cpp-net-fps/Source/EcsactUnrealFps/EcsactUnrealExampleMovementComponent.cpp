#include "EcsactUnrealExampleMovementComponent.h"

auto UEcsactUnrealExampleMovementComponent::TickComponent(
	float                        DeltaTime,
	enum ELevelTick              TickType,
	FActorComponentTickFunction* ThisTickFunction
) -> void {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Velocity = FVector{MoveDirY, MoveDirX, 0.0} * 600.f;
	auto rotation = UpdatedComponent->GetComponentRotation();

	if(MoveDirX != 0.0f || MoveDirY != 0.0f) {
		auto move_vector = FVector{
			MoveDirX,
			-MoveDirY,
			GetActorLocation().Z,
		};

		rotation = move_vector.ToOrientationRotator();
		rotation.Pitch = 0.f;
	}

	auto displacement = Velocity * DeltaTime;
	auto hit_result = FHitResult{};
	SafeMoveUpdatedComponent(displacement, rotation, false, hit_result);

	// UE_LOG(LogTemp, Log, TEXT("%s"), *Velocity.ToString());

	// UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *Velocity.ToString());
}

auto UEcsactUnrealExampleMovementComponent::SetMoveDirection( //
	float X,
	float Y
) -> void {
	MoveDirX = X;
	MoveDirY = Y;
}

auto UEcsactUnrealExampleMovementComponent::IsMoveDirectionSimilar( //
	float X,
	float Y
) const -> bool {
	return MoveDirX == X && MoveDirY == Y;
}
