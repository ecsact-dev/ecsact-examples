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
struct FExampleFpsMassentity {
	GENERATED_BODY()
	
	static FExampleFpsMassentity FromEcsactComponentData(const void*);
	
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
	int32 TickCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "-32768", ClampMax = "32767"))
	int32 ForceX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "-32768", ClampMax = "32767"))
	int32 ForceY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "-32768", ClampMax = "32767"))
	int32 ForceZ;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsToggle {
	GENERATED_BODY()
	
	static FExampleFpsToggle FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "-128", ClampMax = "127"))
	int32 Streaming;
	
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
	void RawInitRotation(int32 Entity, const void* Component);
	void RawUpdateRotation(int32 Entity, const void* Component);
	void RawRemoveRotation(int32 Entity, const void* Component);
	void RawInitPosition(int32 Entity, const void* Component);
	void RawUpdatePosition(int32 Entity, const void* Component);
	void RawRemovePosition(int32 Entity, const void* Component);
	void RawInitMassentity(int32 Entity, const void* Component);
	void RawUpdateMassentity(int32 Entity, const void* Component);
	void RawRemoveMassentity(int32 Entity, const void* Component);
	void RawInitVelocity(int32 Entity, const void* Component);
	void RawUpdateVelocity(int32 Entity, const void* Component);
	void RawRemoveVelocity(int32 Entity, const void* Component);
	void RawInitPushing(int32 Entity, const void* Component);
	void RawUpdatePushing(int32 Entity, const void* Component);
	void RawRemovePushing(int32 Entity, const void* Component);
	void RawInitToggle(int32 Entity, const void* Component);
	void RawUpdateToggle(int32 Entity, const void* Component);
	void RawRemoveToggle(int32 Entity, const void* Component);
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
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.MassEntity"))
	void InitMassentity(int32 Entity, FExampleFpsMassentity Massentity);
	virtual void InitMassentity_Implementation(int32 Entity, FExampleFpsMassentity Massentity);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.MassEntity"))
	void UpdateMassentity(int32 Entity, FExampleFpsMassentity Massentity);
	virtual void UpdateMassentity_Implementation(int32 Entity, FExampleFpsMassentity Massentity);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.MassEntity"))
	void RemoveMassentity(int32 Entity, FExampleFpsMassentity Massentity);
	virtual void RemoveMassentity_Implementation(int32 Entity, FExampleFpsMassentity Massentity);
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
