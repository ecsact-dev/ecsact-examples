#pragma once

#include "Components/SceneComponent.h"
#include "ecsact/runtime/common.h"
#include "EcsactActor.generated.h"

UCLASS(
	BlueprintType,
	ClassGroup = (EcsactUnrealFps),
	meta = (BlueprintSpawnableComponent)
)

class UEcsactActor : public USceneComponent {
	GENERATED_BODY()
	ecsact_entity_id EntityId = ECSACT_INVALID_ID(entity);
	FTimerHandle     TimerHandle;

	auto OnEntityCreated(ecsact_entity_id CreatedEntityId) -> void;
	auto TimeDelayWorkaround() -> void;

public:
	UEcsactActor();

	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		meta = (Tooltip = "Send position/rotation as ecsact stream data")
	)
	bool bStreamEcsactStreamData = true;

	auto GetEntityId() const -> ecsact_entity_id;
	auto BeginPlay() -> void override;

	auto IsComponentTickEnabled() const -> bool override;

	auto TickComponent(
		float                        DeltaTime,
		enum ELevelTick              TickType,
		FActorComponentTickFunction* ThisTickFunction
	) -> void override;
};
