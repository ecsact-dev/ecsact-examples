#include "EcsactTracker.h"

#include "StateTreeLinker.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnrealFps/EcsactPlayerEntitySpawner.h"
#include "EcsactUnreal/EcsactRunner.h"

FEcsactTracker::FEcsactTracker() {
}

bool FEcsactTracker::Link(FStateTreeLinker& Linker) {
	Linker.LinkExternalData(StreamFragmentHandle);
	return FMassStateTreeTaskBase::Link(Linker);
}

// EStateTreeRunStatus FEcsactTracker::EnterState(
// 	FStateTreeExecutionContext&       Context,
// 	const FStateTreeTransitionResult& Transition
// ) const {
// }

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

	const auto& StreamingFragment = Context.GetExternalData(StreamFragmentHandle);

	if(InstanceData.bIsStreaming != StreamingFragment.ShouldStream()) {
		UE_LOG(
			LogTemp,
			Log,
			TEXT("Setting Is Stream to: %i"),
			StreamingFragment.ShouldStream()
		);
	}
	InstanceData.bIsStreaming = StreamingFragment.ShouldStream();

	return EStateTreeRunStatus::Running;
}
