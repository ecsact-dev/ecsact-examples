#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EcsactUnreal/EcsactRunnerSubsystem.h"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps__ecsact__ue.generated.h"


USTRUCT(BlueprintType)
struct FExampleFpsProjectile {
	GENERATED_BODY()
	
	static FExampleFpsProjectile FromEcsactComponentData(const void*);
	
};

USTRUCT(BlueprintType)
struct FExampleFpsPlayer {
	GENERATED_BODY()
	
	static FExampleFpsPlayer FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerId;
	
};

USTRUCT(BlueprintType)
struct FExampleFpsFiring {
	GENERATED_BODY()
	
	static FExampleFpsFiring FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LastFireTick;
	
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

UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Ecsact Runner Package Subsystem (example.fps)"))
class UExampleFpsEcsactRunnerSubsystem : public UEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT
	
	TArray<void(ThisClass::*)(int32, const void*)> InitComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> UpdateComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> RemoveComponentFns;
	void RawInitProjectile(int32 Entity, const void* Component);
	void RawUpdateProjectile(int32 Entity, const void* Component);
	void RawRemoveProjectile(int32 Entity, const void* Component);
	void RawInitPlayer(int32 Entity, const void* Component);
	void RawUpdatePlayer(int32 Entity, const void* Component);
	void RawRemovePlayer(int32 Entity, const void* Component);
	void RawInitFiring(int32 Entity, const void* Component);
	void RawUpdateFiring(int32 Entity, const void* Component);
	void RawRemoveFiring(int32 Entity, const void* Component);
	void RawInitRotation(int32 Entity, const void* Component);
	void RawUpdateRotation(int32 Entity, const void* Component);
	void RawRemoveRotation(int32 Entity, const void* Component);
	void RawInitPosition(int32 Entity, const void* Component);
	void RawUpdatePosition(int32 Entity, const void* Component);
	void RawRemovePosition(int32 Entity, const void* Component);
	
protected:
	void InitComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void UpdateComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void RemoveComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	
	
public:
	UExampleFpsEcsactRunnerSubsystem();
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Projectile"))
	void InitProjectile(int32 Entity, FExampleFpsProjectile Projectile);
	virtual void InitProjectile_Implementation(int32 Entity, FExampleFpsProjectile Projectile);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Projectile"))
	void UpdateProjectile(int32 Entity, FExampleFpsProjectile Projectile);
	virtual void UpdateProjectile_Implementation(int32 Entity, FExampleFpsProjectile Projectile);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Projectile"))
	void RemoveProjectile(int32 Entity, FExampleFpsProjectile Projectile);
	virtual void RemoveProjectile_Implementation(int32 Entity, FExampleFpsProjectile Projectile);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Player"))
	void InitPlayer(int32 Entity, FExampleFpsPlayer Player);
	virtual void InitPlayer_Implementation(int32 Entity, FExampleFpsPlayer Player);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Player"))
	void UpdatePlayer(int32 Entity, FExampleFpsPlayer Player);
	virtual void UpdatePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Player"))
	void RemovePlayer(int32 Entity, FExampleFpsPlayer Player);
	virtual void RemovePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.fps.Firing"))
	void InitFiring(int32 Entity, FExampleFpsFiring Firing);
	virtual void InitFiring_Implementation(int32 Entity, FExampleFpsFiring Firing);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.fps.Firing"))
	void UpdateFiring(int32 Entity, FExampleFpsFiring Firing);
	virtual void UpdateFiring_Implementation(int32 Entity, FExampleFpsFiring Firing);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.fps.Firing"))
	void RemoveFiring(int32 Entity, FExampleFpsFiring Firing);
	virtual void RemoveFiring_Implementation(int32 Entity, FExampleFpsFiring Firing);
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
	
};
