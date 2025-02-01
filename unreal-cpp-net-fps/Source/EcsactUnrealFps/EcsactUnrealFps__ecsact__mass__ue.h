#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "MassEntityConfigAsset.h"
#include "ecsact/runtime/common.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps__ecsact__mass__ue.generated.h"

USTRUCT()
struct FEcsactEntityFragment : public FMassFragment {
	GENERATED_BODY()
	FEcsactEntityFragment() = default;
	FEcsactEntityFragment(const ecsact_entity_id EntityId) : id(EntityId) {}
	
	ecsact_entity_id GetId() const {
		return id;
		
	}
	private:
	ecsact_entity_id id;
};
USTRUCT()
struct FExampleFpsPlayerFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsPlayerFragment() = default;
	FExampleFpsPlayerFragment(FExampleFpsPlayer in_component) : component(in_component){}
	
	FExampleFpsPlayer component;
};
USTRUCT()
struct FExampleFpsPusherFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsPusherFragment() = default;
	FExampleFpsPusherFragment(FExampleFpsPusher in_component) : component(in_component){}
	
	FExampleFpsPusher component;
};
USTRUCT()
struct FExampleFpsPusherexpiredFragment : public FMassTag {
	GENERATED_BODY()
	
};
USTRUCT()
struct FExampleFpsRotationFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsRotationFragment() = default;
	FExampleFpsRotationFragment(FExampleFpsRotation in_component) : component(in_component){}
	
	FExampleFpsRotation component;
};
USTRUCT()
struct FExampleFpsPositionFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsPositionFragment() = default;
	FExampleFpsPositionFragment(FExampleFpsPosition in_component) : component(in_component){}
	
	FExampleFpsPosition component;
};
USTRUCT()
struct FExampleFpsStunnedFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsStunnedFragment() = default;
	FExampleFpsStunnedFragment(FExampleFpsStunned in_component) : component(in_component){}
	
	FExampleFpsStunned component;
};
USTRUCT()
struct FExampleFpsStunnedexpiredFragment : public FMassTag {
	GENERATED_BODY()
	
};
USTRUCT()
struct FExampleFpsPushchargeFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsPushchargeFragment() = default;
	FExampleFpsPushchargeFragment(FExampleFpsPushcharge in_component) : component(in_component){}
	
	FExampleFpsPushcharge component;
};
USTRUCT()
struct FExampleFpsEnemyFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsEnemyFragment() = default;
	FExampleFpsEnemyFragment(FExampleFpsEnemy in_component) : component(in_component){}
	
	FExampleFpsEnemy component;
};
USTRUCT()
struct FExampleFpsVelocityFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsVelocityFragment() = default;
	FExampleFpsVelocityFragment(FExampleFpsVelocity in_component) : component(in_component){}
	
	FExampleFpsVelocity component;
};
USTRUCT()
struct FExampleFpsPushingFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsPushingFragment() = default;
	FExampleFpsPushingFragment(FExampleFpsPushing in_component) : component(in_component){}
	
	FExampleFpsPushing component;
};
USTRUCT()
struct FExampleFpsToggleFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsToggleFragment() = default;
	FExampleFpsToggleFragment(FExampleFpsToggle in_component) : component(in_component){}
	
	FExampleFpsToggle component;
};
USTRUCT()
struct FExampleFpsMovedirectionFragment : public FMassFragment {
	GENERATED_BODY()
	
	FExampleFpsMovedirectionFragment() = default;
	FExampleFpsMovedirectionFragment(FExampleFpsMovedirection in_component) : component(in_component){}
	
	FExampleFpsMovedirection component;
};
USTRUCT()
struct FExampleFpsRemovepushingtagFragment : public FMassTag {
	GENERATED_BODY()
	
};

UCLASS(Abstract)
class UExampleFpsMassSpawner : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY()
	
	public:
	virtual auto GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle>;
	void InitPlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) override;
	void UpdatePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) override;
	void RemovePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) override;
	void InitPusher_Implementation(int32 Entity, FExampleFpsPusher Pusher) override;
	void UpdatePusher_Implementation(int32 Entity, FExampleFpsPusher Pusher) override;
	void RemovePusher_Implementation(int32 Entity, FExampleFpsPusher Pusher) override;
	void InitPusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired) override;
	void RemovePusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired) override;
	void InitRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation) override;
	void UpdateRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation) override;
	void RemoveRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation) override;
	void InitPosition_Implementation(int32 Entity, FExampleFpsPosition Position) override;
	void UpdatePosition_Implementation(int32 Entity, FExampleFpsPosition Position) override;
	void RemovePosition_Implementation(int32 Entity, FExampleFpsPosition Position) override;
	void InitStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned) override;
	void UpdateStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned) override;
	void RemoveStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned) override;
	void InitStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired) override;
	void RemoveStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired) override;
	void InitPushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge) override;
	void UpdatePushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge) override;
	void RemovePushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge) override;
	void InitEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy) override;
	void UpdateEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy) override;
	void RemoveEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy) override;
	void InitVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity) override;
	void UpdateVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity) override;
	void RemoveVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity) override;
	void InitPushing_Implementation(int32 Entity, FExampleFpsPushing Pushing) override;
	void UpdatePushing_Implementation(int32 Entity, FExampleFpsPushing Pushing) override;
	void RemovePushing_Implementation(int32 Entity, FExampleFpsPushing Pushing) override;
	void InitToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle) override;
	void UpdateToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle) override;
	void RemoveToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle) override;
	void InitMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection) override;
	void UpdateMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection) override;
	void RemoveMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection) override;
	void InitRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag) override;
	void RemoveRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag) override;
	
};

UCLASS(Abstract)
class UOneToOneExampleFpsMassSpawner : public UExampleFpsMassSpawner {
	GENERATED_BODY()
	
	TMap<ecsact_entity_id, TArray<FMassEntityHandle>> MassEntities;
	protected:
	UPROPERTY(EditAnywhere)
	UMassEntityConfigAsset* MassEntityConfigAsset;
	auto EntityCreated_Implementation(int32 Entity) -> void override;
	auto EntityDestroyed_Implementation(int32 Entity) -> void override;
	auto GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle> override;
	virtual auto GetEntityMassConfig() const -> UMassEntityConfigAsset*;
	
};
