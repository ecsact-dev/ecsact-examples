#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Example__ecsact__ue.h"
#include "EntitySpawner.generated.h"

UCLASS(Abstract)

class ECSACTUNREALCPPBASIC_API UEntitySpawner
	: public UExampleEcsactRunnerSubsystem {
	GENERATED_BODY()

	TMap<int32, AActor*> EntityActors;

	UPROPERTY(EditAnywhere)
	class UWorld* EntitySpawnerWorld;

	auto OnPreWorldInitialization( //
		UWorld*,
		const UWorld::InitializationValues
	) -> void;
	auto OnPostWorldCleanup( //
		UWorld*,
		bool bSessionEnded,
		bool bCleanupResources
	) -> void;

public:
	UFUNCTION(BlueprintCallable)
	static void CreateEntitySpawnPoint();

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TSubclassOf<class AActor> EntityActorClass;

	UEntitySpawner();

	auto GetWorld() const -> class UWorld* override;

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
