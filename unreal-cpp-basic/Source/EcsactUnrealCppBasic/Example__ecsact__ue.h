#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EcsactUnreal/EcsactRunnerSubsystem.h"
#include "Example.ecsact.hh"
#include "Example__ecsact__ue.generated.h"


USTRUCT(BlueprintType)
struct FExamplePosition {
	GENERATED_BODY()
	
	static FExamplePosition FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Z;
	
};

USTRUCT(BlueprintType)
struct FExampleVelocity {
	GENERATED_BODY()
	
	static FExampleVelocity FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Z;
	
};

UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Ecsact Runner Package Subsystem (example)"))
class UExampleEcsactRunnerSubsystem : public UEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT
	
	TArray<void(ThisClass::*)(int32, const void*)> InitComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> UpdateComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> RemoveComponentFns;
	void RawInitPosition(int32 Entity, const void* Component);
	void RawUpdatePosition(int32 Entity, const void* Component);
	void RawRemovePosition(int32 Entity, const void* Component);
	void RawInitVelocity(int32 Entity, const void* Component);
	void RawUpdateVelocity(int32 Entity, const void* Component);
	void RawRemoveVelocity(int32 Entity, const void* Component);
	
protected:
	void InitComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void UpdateComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void RemoveComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	
	
public:
	UExampleEcsactRunnerSubsystem();
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.Position"))
	void InitPosition(int32 Entity, FExamplePosition Position);
	virtual void InitPosition_Implementation(int32 Entity, FExamplePosition Position);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.Position"))
	void UpdatePosition(int32 Entity, FExamplePosition Position);
	virtual void UpdatePosition_Implementation(int32 Entity, FExamplePosition Position);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.Position"))
	void RemovePosition(int32 Entity, FExamplePosition Position);
	virtual void RemovePosition_Implementation(int32 Entity, FExamplePosition Position);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init example.Velocity"))
	void InitVelocity(int32 Entity, FExampleVelocity Velocity);
	virtual void InitVelocity_Implementation(int32 Entity, FExampleVelocity Velocity);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update example.Velocity"))
	void UpdateVelocity(int32 Entity, FExampleVelocity Velocity);
	virtual void UpdateVelocity_Implementation(int32 Entity, FExampleVelocity Velocity);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove example.Velocity"))
	void RemoveVelocity(int32 Entity, FExampleVelocity Velocity);
	virtual void RemoveVelocity_Implementation(int32 Entity, FExampleVelocity Velocity);
	
};
