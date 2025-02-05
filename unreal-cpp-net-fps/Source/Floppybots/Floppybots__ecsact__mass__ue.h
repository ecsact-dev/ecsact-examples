#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "MassEntityConfigAsset.h"
#include "ecsact/runtime/common.h"
#include "Floppybots__ecsact__ue.h"
#include "Floppybots.ecsact.hh"
#include "Floppybots__ecsact__mass__ue.generated.h"

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
struct FFloppybotsPlayerFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsPlayerFragment() = default;
	FFloppybotsPlayerFragment(FFloppybotsPlayer in_component) : component(in_component){}
	
	FFloppybotsPlayer component;
};
USTRUCT()
struct FFloppybotsPusherFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsPusherFragment() = default;
	FFloppybotsPusherFragment(FFloppybotsPusher in_component) : component(in_component){}
	
	FFloppybotsPusher component;
};
USTRUCT()
struct FFloppybotsPusherexpiredFragment : public FMassTag {
	GENERATED_BODY()
	
};
USTRUCT()
struct FFloppybotsRotationFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsRotationFragment() = default;
	FFloppybotsRotationFragment(FFloppybotsRotation in_component) : component(in_component){}
	
	FFloppybotsRotation component;
};
USTRUCT()
struct FFloppybotsPositionFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsPositionFragment() = default;
	FFloppybotsPositionFragment(FFloppybotsPosition in_component) : component(in_component){}
	
	FFloppybotsPosition component;
};
USTRUCT()
struct FFloppybotsStunnedFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsStunnedFragment() = default;
	FFloppybotsStunnedFragment(FFloppybotsStunned in_component) : component(in_component){}
	
	FFloppybotsStunned component;
};
USTRUCT()
struct FFloppybotsStunnedexpiredFragment : public FMassTag {
	GENERATED_BODY()
	
};
USTRUCT()
struct FFloppybotsPushchargeFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsPushchargeFragment() = default;
	FFloppybotsPushchargeFragment(FFloppybotsPushcharge in_component) : component(in_component){}
	
	FFloppybotsPushcharge component;
};
USTRUCT()
struct FFloppybotsEnemyFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsEnemyFragment() = default;
	FFloppybotsEnemyFragment(FFloppybotsEnemy in_component) : component(in_component){}
	
	FFloppybotsEnemy component;
};
USTRUCT()
struct FFloppybotsVelocityFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsVelocityFragment() = default;
	FFloppybotsVelocityFragment(FFloppybotsVelocity in_component) : component(in_component){}
	
	FFloppybotsVelocity component;
};
USTRUCT()
struct FFloppybotsPushingFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsPushingFragment() = default;
	FFloppybotsPushingFragment(FFloppybotsPushing in_component) : component(in_component){}
	
	FFloppybotsPushing component;
};
USTRUCT()
struct FFloppybotsToggleFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsToggleFragment() = default;
	FFloppybotsToggleFragment(FFloppybotsToggle in_component) : component(in_component){}
	
	FFloppybotsToggle component;
};
USTRUCT()
struct FFloppybotsMovedirectionFragment : public FMassFragment {
	GENERATED_BODY()
	
	FFloppybotsMovedirectionFragment() = default;
	FFloppybotsMovedirectionFragment(FFloppybotsMovedirection in_component) : component(in_component){}
	
	FFloppybotsMovedirection component;
};
USTRUCT()
struct FFloppybotsRemovepushingtagFragment : public FMassTag {
	GENERATED_BODY()
	
};

UCLASS(Abstract)
class UFloppybotsMassSpawner : public UFloppybotsEcsactRunnerSubsystem {
	GENERATED_BODY()
	
	public:
	virtual auto GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle>;
	void InitPlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) override;
	void UpdatePlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) override;
	void RemovePlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) override;
	void InitPusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) override;
	void UpdatePusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) override;
	void RemovePusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) override;
	void InitPusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired) override;
	void RemovePusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired) override;
	void InitRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) override;
	void UpdateRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) override;
	void RemoveRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) override;
	void InitPosition_Implementation(int32 Entity, FFloppybotsPosition Position) override;
	void UpdatePosition_Implementation(int32 Entity, FFloppybotsPosition Position) override;
	void RemovePosition_Implementation(int32 Entity, FFloppybotsPosition Position) override;
	void InitStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) override;
	void UpdateStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) override;
	void RemoveStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) override;
	void InitStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired) override;
	void RemoveStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired) override;
	void InitPushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) override;
	void UpdatePushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) override;
	void RemovePushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) override;
	void InitEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) override;
	void UpdateEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) override;
	void RemoveEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) override;
	void InitVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) override;
	void UpdateVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) override;
	void RemoveVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) override;
	void InitPushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) override;
	void UpdatePushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) override;
	void RemovePushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) override;
	void InitToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) override;
	void UpdateToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) override;
	void RemoveToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) override;
	void InitMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) override;
	void UpdateMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) override;
	void RemoveMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) override;
	void InitRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag) override;
	void RemoveRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag) override;
	
};

UCLASS(Abstract)
class UOneToOneFloppybotsMassSpawner : public UFloppybotsMassSpawner {
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
