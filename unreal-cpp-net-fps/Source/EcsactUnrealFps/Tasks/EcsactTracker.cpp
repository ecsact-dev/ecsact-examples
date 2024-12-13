#include "EcsactTracker.h"

#include "StateTreeLinker.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnrealFps/EcsactPlayerEntitySpawner.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnrealFps/EcsactUnrealFpsCharacter.h"

FEcsactTracker::FEcsactTracker() {
}

bool FEcsactTracker::Link(FStateTreeLinker& Linker) {
	return Super::Link(Linker);
}

EStateTreeRunStatus FEcsactTracker::EnterState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	InstanceData.bIsStreaming = true;

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FEcsactTracker::Tick( //
	FStateTreeExecutionContext& Context,
	const float                 DeltaTime
) const {
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	auto runner = EcsactUnrealExecution::Runner(Context.GetWorld()).Get();
	check(runner);
	auto PlayerSpawner = runner->GetSubsystem<UEcsactPlayerEntitySpawner>();

	// TODO: We currently only get the first player to follow instead of
	// accounting for X amount
	if(PlayerSpawner->PlayerEntities.Num() > 0) {
		auto ActorWeakPtr = PlayerSpawner->PlayerEntities.begin().Value();
		if(ActorWeakPtr.IsValid()) {
			auto* pawn = ActorWeakPtr.Get();

			InstanceData.PlayerPosition = pawn->GetActorLocation();
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Player Actor is invalid"));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No players to follow"));
	}

	return EStateTreeRunStatus::Running;
}
