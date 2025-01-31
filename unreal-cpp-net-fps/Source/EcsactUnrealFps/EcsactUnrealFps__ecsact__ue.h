#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EcsactUnreal/EcsactRunnerSubsystem.h"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps__ecsact__ue.generated.h"


USTRUCT(BlueprintType)
struct FExampleFpsPlayer {
	GENERATED_BODY()
	
	static FExampleFpsPlayer FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerId;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsPusher {
	GENERATED_BODY()
	
	static FExampleFpsPusher FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownRemaining;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsPusherexpired {
	GENERATED_BODY()
	
	static FExampleFpsPusherexpired FromEcsactComponentData(const void*);
	
};

USTRUCT(BlueprintType)
struct FExampleFpsRotation {
	GENERATED_BODY()
	
	static FExampleFpsRotation FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Yaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Roll;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsPosition {
	GENERATED_BODY()
	
	static FExampleFpsPosition FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Z;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsStunned {
	GENERATED_BODY()
	
	static FExampleFpsStunned FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Remaining;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsStunnedexpired {
	GENERATED_BODY()
	
	static FExampleFpsStunnedexpired FromEcsactComponentData(const void*);
	
};

USTRUCT(BlueprintType)
struct FExampleFpsPushcharge {
	GENERATED_BODY()
	
	static FExampleFpsPushcharge FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsEnemy {
	GENERATED_BODY()
	
	static FExampleFpsEnemy FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerId;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsVelocity {
	GENERATED_BODY()
	
	static FExampleFpsVelocity FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Z;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsPushing {
	GENERATED_BODY()
	
	static FExampleFpsPushing FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "-32768", ClampMax = "32767"))
	int32 TickTotal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "-32768", ClampMax = "32767"))
	int32 TickCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForceX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForceY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForceZ;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsToggle {
	GENERATED_BODY()
	
	static FExampleFpsToggle FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "-128", ClampMax = "127"))
	int32 Streaming;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsMovedirection {
	GENERATED_BODY()
	
	static FExampleFpsMovedirection FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Y;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsRemovepushingtag {
	GENERATED_BODY()
	
	static FExampleFpsRemovepushingtag FromEcsactComponentData(const void*);
	
};

UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Ecsact Runner Package Subsystem (example.fps)"))
class UExampleFpsEcsactRunnerSubsystem : public UEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT
	
	TArray<void(ThisClass::*)(int32, const void*)> InitComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> UpdateComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> RemoveComponentFns;
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
	UExampleFpsEcsactRunnerSubsystem();
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Player"))
	void InitPlayer(int32 Entity, FExampleFpsPlayer Player);
	virtual void InitPlayer_Implementation(int32 Entity, FExampleFpsPlayer Player);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Player"))
	void UpdatePlayer(int32 Entity, FExampleFpsPlayer Player);
	virtual void UpdatePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Player"))
	void RemovePlayer(int32 Entity, FExampleFpsPlayer Player);
	virtual void RemovePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Pusher"))
	void InitPusher(int32 Entity, FExampleFpsPusher Pusher);
	virtual void InitPusher_Implementation(int32 Entity, FExampleFpsPusher Pusher);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Pusher"))
	void UpdatePusher(int32 Entity, FExampleFpsPusher Pusher);
	virtual void UpdatePusher_Implementation(int32 Entity, FExampleFpsPusher Pusher);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Pusher"))
	void RemovePusher(int32 Entity, FExampleFpsPusher Pusher);
	virtual void RemovePusher_Implementation(int32 Entity, FExampleFpsPusher Pusher);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.PusherExpired"))
	void InitPusherexpired(int32 Entity, FExampleFpsPusherexpired Pusherexpired);
	virtual void InitPusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.PusherExpired"))
	void UpdatePusherexpired(int32 Entity, FExampleFpsPusherexpired Pusherexpired);
	virtual void UpdatePusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.PusherExpired"))
	void RemovePusherexpired(int32 Entity, FExampleFpsPusherexpired Pusherexpired);
	virtual void RemovePusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Rotation"))
	void InitRotation(int32 Entity, FExampleFpsRotation Rotation);
	virtual void InitRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Rotation"))
	void UpdateRotation(int32 Entity, FExampleFpsRotation Rotation);
	virtual void UpdateRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Rotation"))
	void RemoveRotation(int32 Entity, FExampleFpsRotation Rotation);
	virtual void RemoveRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Position"))
	void InitPosition(int32 Entity, FExampleFpsPosition Position);
	virtual void InitPosition_Implementation(int32 Entity, FExampleFpsPosition Position);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Position"))
	void UpdatePosition(int32 Entity, FExampleFpsPosition Position);
	virtual void UpdatePosition_Implementation(int32 Entity, FExampleFpsPosition Position);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Position"))
	void RemovePosition(int32 Entity, FExampleFpsPosition Position);
	virtual void RemovePosition_Implementation(int32 Entity, FExampleFpsPosition Position);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Stunned"))
	void InitStunned(int32 Entity, FExampleFpsStunned Stunned);
	virtual void InitStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Stunned"))
	void UpdateStunned(int32 Entity, FExampleFpsStunned Stunned);
	virtual void UpdateStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Stunned"))
	void RemoveStunned(int32 Entity, FExampleFpsStunned Stunned);
	virtual void RemoveStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.StunnedExpired"))
	void InitStunnedexpired(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired);
	virtual void InitStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.StunnedExpired"))
	void UpdateStunnedexpired(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired);
	virtual void UpdateStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.StunnedExpired"))
	void RemoveStunnedexpired(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired);
	virtual void RemoveStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.PushCharge"))
	void InitPushcharge(int32 Entity, FExampleFpsPushcharge Pushcharge);
	virtual void InitPushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.PushCharge"))
	void UpdatePushcharge(int32 Entity, FExampleFpsPushcharge Pushcharge);
	virtual void UpdatePushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.PushCharge"))
	void RemovePushcharge(int32 Entity, FExampleFpsPushcharge Pushcharge);
	virtual void RemovePushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Enemy"))
	void InitEnemy(int32 Entity, FExampleFpsEnemy Enemy);
	virtual void InitEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Enemy"))
	void UpdateEnemy(int32 Entity, FExampleFpsEnemy Enemy);
	virtual void UpdateEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Enemy"))
	void RemoveEnemy(int32 Entity, FExampleFpsEnemy Enemy);
	virtual void RemoveEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Velocity"))
	void InitVelocity(int32 Entity, FExampleFpsVelocity Velocity);
	virtual void InitVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Velocity"))
	void UpdateVelocity(int32 Entity, FExampleFpsVelocity Velocity);
	virtual void UpdateVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Velocity"))
	void RemoveVelocity(int32 Entity, FExampleFpsVelocity Velocity);
	virtual void RemoveVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Pushing"))
	void InitPushing(int32 Entity, FExampleFpsPushing Pushing);
	virtual void InitPushing_Implementation(int32 Entity, FExampleFpsPushing Pushing);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Pushing"))
	void UpdatePushing(int32 Entity, FExampleFpsPushing Pushing);
	virtual void UpdatePushing_Implementation(int32 Entity, FExampleFpsPushing Pushing);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Pushing"))
	void RemovePushing(int32 Entity, FExampleFpsPushing Pushing);
	virtual void RemovePushing_Implementation(int32 Entity, FExampleFpsPushing Pushing);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Toggle"))
	void InitToggle(int32 Entity, FExampleFpsToggle Toggle);
	virtual void InitToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Toggle"))
	void UpdateToggle(int32 Entity, FExampleFpsToggle Toggle);
	virtual void UpdateToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Toggle"))
	void RemoveToggle(int32 Entity, FExampleFpsToggle Toggle);
	virtual void RemoveToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.MoveDirection"))
	void InitMovedirection(int32 Entity, FExampleFpsMovedirection Movedirection);
	virtual void InitMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.MoveDirection"))
	void UpdateMovedirection(int32 Entity, FExampleFpsMovedirection Movedirection);
	virtual void UpdateMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.MoveDirection"))
	void RemoveMovedirection(int32 Entity, FExampleFpsMovedirection Movedirection);
	virtual void RemoveMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.RemovePushingTag"))
	void InitRemovepushingtag(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag);
	virtual void InitRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.RemovePushingTag"))
	void UpdateRemovepushingtag(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag);
	virtual void UpdateRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.RemovePushingTag"))
	void RemoveRemovepushingtag(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag);
	virtual void RemoveRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag);
	
};
