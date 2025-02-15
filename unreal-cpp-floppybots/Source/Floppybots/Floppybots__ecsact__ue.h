#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <array>
#include "ecsact/runtime/common.h"
#include "EcsactUnreal/Ecsact.h"
#include "EcsactUnreal/EcsactRunnerSubsystem.h"
#include "Floppybots.ecsact.hh"
#include "Floppybots__ecsact__ue.generated.h"

namespace EcsactUnreal::CodegenMeta {
	constexpr auto FloppybotsSystemLikeIds = std::array<ecsact_system_like_id, 16>{
		static_cast<ecsact_system_like_id>(13 /* floppybots.StunTimer */),
		static_cast<ecsact_system_like_id>(14 /* floppybots.PusherExpireChecker */),
		static_cast<ecsact_system_like_id>(15 /* floppybots.PusherApplyExpired */),
		static_cast<ecsact_system_like_id>(18 /* floppybots.FinishPush.PushEntities */),
		static_cast<ecsact_system_like_id>(19 /* floppybots.RemovePushCharge */),
		static_cast<ecsact_system_like_id>(20 /* floppybots.TickPushCharge */),
		static_cast<ecsact_system_like_id>(24 /* floppybots.ApplyPush */),
		static_cast<ecsact_system_like_id>(25 /* floppybots.ApplyVelocity */),
		static_cast<ecsact_system_like_id>(26 /* floppybots.ApplyDrag */),
		static_cast<ecsact_system_like_id>(27 /* floppybots.ResumeStreaming */),
		static_cast<ecsact_system_like_id>(28 /* floppybots.TogglePushedEntities */),
		static_cast<ecsact_system_like_id>(29 /* floppybots.RemovePushing */),
		static_cast<ecsact_system_like_id>(30 /* floppybots.StunnedExpiry */),
		static_cast<ecsact_system_like_id>(16 /* floppybots.StartPush */),
		static_cast<ecsact_system_like_id>(17 /* floppybots.FinishPush */),
		static_cast<ecsact_system_like_id>(22 /* floppybots.Move */),
	};

	constexpr auto FloppybotsExportNames = std::array<const char*, 16>{
		"floppybots__StunTimer",
		"floppybots__PusherExpireChecker",
		"floppybots__PusherApplyExpired",
		"floppybots__FinishPush__PushEntities",
		"floppybots__RemovePushCharge",
		"floppybots__TickPushCharge",
		"floppybots__ApplyPush",
		"floppybots__ApplyVelocity",
		"floppybots__ApplyDrag",
		"floppybots__ResumeStreaming",
		"floppybots__TogglePushedEntities",
		"floppybots__RemovePushing",
		"floppybots__StunnedExpiry",
		"floppybots__StartPush",
		"floppybots__FinishPush",
		"floppybots__Move",
	};

} // namespace EcsactUnreal::CodegenMeta

/* removed some for sake of video (screenshot size was too big) */

UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Ecsact Runner Package Subsystem (floppybots)"))
class UFloppybotsEcsactRunnerSubsystem : public UEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	TArray<void (ThisClass::*)(int32, const void*)> InitComponentFns;
	TArray<void (ThisClass::*)(int32, const void*)> UpdateComponentFns;
	TArray<void (ThisClass::*)(int32, const void*)> RemoveComponentFns;
	void RawInitPlayer(int32 Entity, const void* Component);
	void RawUpdatePlayer(int32 Entity, const void* Component);
	void RawRemovePlayer(int32 Entity, const void* Component);
	void RawInitPusher(int32 Entity, const void* Component);
	void RawUpdatePusher(int32 Entity, const void* Component);
	void RawRemovePusher(int32 Entity, const void* Component);
	void RawInitPusherexpired(int32 Entity, const void* Component);
	void RawUpdatePusherexpired(int32 Entity, const void* Component);
	void RawRemovePusherexpired(int32 Entity, const void* Component);
	void RawInitRotation(int32 Entity, const void* Component);
	void RawUpdateRotation(int32 Entity, const void* Component);
	void RawRemoveRotation(int32 Entity, const void* Component);
	void RawInitPosition(int32 Entity, const void* Component);
	void RawUpdatePosition(int32 Entity, const void* Component);
	void RawRemovePosition(int32 Entity, const void* Component);
	void RawInitStunned(int32 Entity, const void* Component);
	void RawUpdateStunned(int32 Entity, const void* Component);
	void RawRemoveStunned(int32 Entity, const void* Component);
	void RawInitStunnedexpired(int32 Entity, const void* Component);
	void RawUpdateStunnedexpired(int32 Entity, const void* Component);
	void RawRemoveStunnedexpired(int32 Entity, const void* Component);
	void RawInitPushcharge(int32 Entity, const void* Component);
	void RawUpdatePushcharge(int32 Entity, const void* Component);
	void RawRemovePushcharge(int32 Entity, const void* Component);
	void RawInitEnemy(int32 Entity, const void* Component);
	void RawUpdateEnemy(int32 Entity, const void* Component);
	void RawRemoveEnemy(int32 Entity, const void* Component);
	void RawInitVelocity(int32 Entity, const void* Component);
	void RawUpdateVelocity(int32 Entity, const void* Component);
	void RawRemoveVelocity(int32 Entity, const void* Component);
	void RawInitPushing(int32 Entity, const void* Component);
	void RawUpdatePushing(int32 Entity, const void* Component);
	void RawRemovePushing(int32 Entity, const void* Component);
	void RawInitToggle(int32 Entity, const void* Component);
	void RawUpdateToggle(int32 Entity, const void* Component);
	void RawRemoveToggle(int32 Entity, const void* Component);
	void RawInitMovedirection(int32 Entity, const void* Component);
	void RawUpdateMovedirection(int32 Entity, const void* Component);
	void RawRemoveMovedirection(int32 Entity, const void* Component);
	void RawInitRemovepushingtag(int32 Entity, const void* Component);
	void RawUpdateRemovepushingtag(int32 Entity, const void* Component);
	void RawRemoveRemovepushingtag(int32 Entity, const void* Component);

protected:
	void InitComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void UpdateComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void RemoveComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;

public:
	UFloppybotsEcsactRunnerSubsystem();

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Player"))
	void InitPlayer(int32 Entity, FFloppybotsPlayer Player);
	virtual void InitPlayer_Implementation(int32 Entity, FFloppybotsPlayer Player);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Player"))
	void UpdatePlayer(int32 Entity, FFloppybotsPlayer Player);
	virtual void UpdatePlayer_Implementation(int32 Entity, FFloppybotsPlayer Player);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Player"))
	void RemovePlayer(int32 Entity, FFloppybotsPlayer Player);
	virtual void RemovePlayer_Implementation(int32 Entity, FFloppybotsPlayer Player);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Pusher"))
	void InitPusher(int32 Entity, FFloppybotsPusher Pusher);
	virtual void InitPusher_Implementation(int32 Entity, FFloppybotsPusher Pusher);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Pusher"))
	void UpdatePusher(int32 Entity, FFloppybotsPusher Pusher);
	virtual void UpdatePusher_Implementation(int32 Entity, FFloppybotsPusher Pusher);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Pusher"))
	void RemovePusher(int32 Entity, FFloppybotsPusher Pusher);
	virtual void RemovePusher_Implementation(int32 Entity, FFloppybotsPusher Pusher);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.PusherExpired"))
	void InitPusherexpired(int32 Entity, FFloppybotsPusherexpired Pusherexpired);
	virtual void InitPusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.PusherExpired"))
	void UpdatePusherexpired(int32 Entity, FFloppybotsPusherexpired Pusherexpired);
	virtual void UpdatePusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.PusherExpired"))
	void RemovePusherexpired(int32 Entity, FFloppybotsPusherexpired Pusherexpired);
	virtual void RemovePusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Rotation"))
	void InitRotation(int32 Entity, FFloppybotsRotation Rotation);
	virtual void InitRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Rotation"))
	void UpdateRotation(int32 Entity, FFloppybotsRotation Rotation);
	virtual void UpdateRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Rotation"))
	void RemoveRotation(int32 Entity, FFloppybotsRotation Rotation);
	virtual void RemoveRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Position"))
	void InitPosition(int32 Entity, FFloppybotsPosition Position);
	virtual void InitPosition_Implementation(int32 Entity, FFloppybotsPosition Position);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Position"))
	void UpdatePosition(int32 Entity, FFloppybotsPosition Position);
	virtual void UpdatePosition_Implementation(int32 Entity, FFloppybotsPosition Position);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Position"))
	void RemovePosition(int32 Entity, FFloppybotsPosition Position);
	virtual void RemovePosition_Implementation(int32 Entity, FFloppybotsPosition Position);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Stunned"))
	void InitStunned(int32 Entity, FFloppybotsStunned Stunned);
	virtual void InitStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Stunned"))
	void UpdateStunned(int32 Entity, FFloppybotsStunned Stunned);
	virtual void UpdateStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Stunned"))
	void RemoveStunned(int32 Entity, FFloppybotsStunned Stunned);
	virtual void RemoveStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.StunnedExpired"))
	void InitStunnedexpired(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired);
	virtual void InitStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.StunnedExpired"))
	void UpdateStunnedexpired(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired);
	virtual void UpdateStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.StunnedExpired"))
	void RemoveStunnedexpired(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired);
	virtual void RemoveStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.PushCharge"))
	void InitPushcharge(int32 Entity, FFloppybotsPushcharge Pushcharge);
	virtual void InitPushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.PushCharge"))
	void UpdatePushcharge(int32 Entity, FFloppybotsPushcharge Pushcharge);
	virtual void UpdatePushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.PushCharge"))
	void RemovePushcharge(int32 Entity, FFloppybotsPushcharge Pushcharge);
	virtual void RemovePushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Enemy"))
	void InitEnemy(int32 Entity, FFloppybotsEnemy Enemy);
	virtual void InitEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Enemy"))
	void UpdateEnemy(int32 Entity, FFloppybotsEnemy Enemy);
	virtual void UpdateEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Enemy"))
	void RemoveEnemy(int32 Entity, FFloppybotsEnemy Enemy);
	virtual void RemoveEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Velocity"))
	void InitVelocity(int32 Entity, FFloppybotsVelocity Velocity);
	virtual void InitVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Velocity"))
	void UpdateVelocity(int32 Entity, FFloppybotsVelocity Velocity);
	virtual void UpdateVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Velocity"))
	void RemoveVelocity(int32 Entity, FFloppybotsVelocity Velocity);
	virtual void RemoveVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Pushing"))
	void InitPushing(int32 Entity, FFloppybotsPushing Pushing);
	virtual void InitPushing_Implementation(int32 Entity, FFloppybotsPushing Pushing);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Pushing"))
	void UpdatePushing(int32 Entity, FFloppybotsPushing Pushing);
	virtual void UpdatePushing_Implementation(int32 Entity, FFloppybotsPushing Pushing);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Pushing"))
	void RemovePushing(int32 Entity, FFloppybotsPushing Pushing);
	virtual void RemovePushing_Implementation(int32 Entity, FFloppybotsPushing Pushing);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.Toggle"))
	void InitToggle(int32 Entity, FFloppybotsToggle Toggle);
	virtual void InitToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.Toggle"))
	void UpdateToggle(int32 Entity, FFloppybotsToggle Toggle);
	virtual void UpdateToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.Toggle"))
	void RemoveToggle(int32 Entity, FFloppybotsToggle Toggle);
	virtual void RemoveToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.MoveDirection"))
	void InitMovedirection(int32 Entity, FFloppybotsMovedirection Movedirection);
	virtual void InitMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.MoveDirection"))
	void UpdateMovedirection(int32 Entity, FFloppybotsMovedirection Movedirection);
	virtual void UpdateMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.MoveDirection"))
	void RemoveMovedirection(int32 Entity, FFloppybotsMovedirection Movedirection);
	virtual void RemoveMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init floppybots.RemovePushingTag"))
	void InitRemovepushingtag(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag);
	virtual void InitRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update floppybots.RemovePushingTag"))
	void UpdateRemovepushingtag(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag);
	virtual void UpdateRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag);

	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove floppybots.RemovePushingTag"))
	void RemoveRemovepushingtag(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag);
	virtual void RemoveRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag);
};
