#include "EcsactActor.h"
#include "CoreGlobals.h"
#include "CoreMinimal.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnrealFps.ecsact.hh"
#include "Logging/LogMacros.h"
#include "Logging/LogVerbosity.h"

UEcsactActor::UEcsactActor() {
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;
}

auto UEcsactActor::GetEntityId() const -> ecsact_entity_id {
	return EntityId;
}

auto UEcsactActor::OnEntityCreated(ecsact_entity_id CreatedEntityId) -> void {
	EntityId = CreatedEntityId;
}

auto UEcsactActor::BeginPlay() -> void {
	Super::BeginPlay();

	// HACK: Need to get signal when runner is ready
	// HACK: there is a bug with either the ecsact unreal integration where only 1
	// entity is created or a bug with async reference where it only considers 1
	auto delay = static_cast<float>(FMath::RandRange(500, 1500)) / 1000.f;
	GetWorld()
		->GetTimerManager()
		.SetTimer(TimerHandle, this, &ThisClass::TimeDelayWorkaround, delay, false);
}

auto UEcsactActor::TimeDelayWorkaround() -> void {
	auto runner = EcsactUnrealExecution::Runner(GetWorld());
	auto comp_loc = GetComponentLocation();
	auto comp_rot = GetComponentRotation();
	runner->CreateEntity()
		.AddComponent(example::fps::Position{
			.x = static_cast<float>(comp_loc.X),
			.y = static_cast<float>(comp_loc.Y),
			.z = static_cast<float>(comp_loc.Z),
		})
		.AddComponent(example::fps::Rotation{
			.pitch = static_cast<float>(comp_rot.Pitch),
			.yaw = static_cast<float>(comp_rot.Yaw),
			.roll = static_cast<float>(comp_rot.Roll),
		})
		.OnCreate(TDelegate<void(ecsact_entity_id)>::CreateUObject(
			this,
			&ThisClass::OnEntityCreated
		));
}

auto UEcsactActor::IsComponentTickEnabled() const -> bool {
	return bStreamEcsactStreamData;
}

auto UEcsactActor::TickComponent(
	float                        DeltaTime,
	enum ELevelTick              TickType,
	FActorComponentTickFunction* ThisTickFunction
) -> void {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(EntityId == ECSACT_INVALID_ID(entity)) {
		return;
	}

	auto runner = EcsactUnrealExecution::Runner(GetWorld());
	if(bStreamEcsactStreamData && runner.IsValid()) {
		auto comp_loc = GetComponentLocation();
		auto comp_rot = GetComponentRotation();
		runner->Stream(
			EntityId,
			example::fps::Position{
				.x = static_cast<float>(comp_loc.X),
				.y = static_cast<float>(comp_loc.Y),
				.z = static_cast<float>(comp_loc.Z),
			}
		);
		runner->Stream(
			EntityId,
			example::fps::Rotation{
				.pitch = static_cast<float>(comp_rot.Pitch),
				.yaw = static_cast<float>(comp_rot.Yaw),
				.roll = static_cast<float>(comp_rot.Roll),
			}
		);
	}
}
