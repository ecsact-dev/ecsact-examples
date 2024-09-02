#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Example__ecsact__ue.h"
#include "EntitySpawner.generated.h"

UCLASS()

class ECSACTUNREALCPPBASIC_API UEntitySpawner
	: public UExampleEcsactRunnerSubsystem {
	GENERATED_BODY()

	TMap<int32, AActor*> EntityActors;

public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TSubclassOf<class AActor> EntityActorClass;

	auto RunnerStart_Implementation(UEcsactRunner* Runner) -> void override;
	auto RunnerStop_Implementation(UEcsactRunner* Runner) -> void override;

	auto InitPosition_Implementation( //
		int32            Entity,
		FExamplePosition Position
	) -> void override;
	auto UpdatePosition_Implementation( //
		int32            Entity,
		FExamplePosition Position
	) -> void override;
	auto RemovePosition_Implementation( //
		int32            Entity,
		FExamplePosition Position
	) -> void override;
};
