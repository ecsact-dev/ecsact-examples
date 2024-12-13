#include "EcsactIdle.h"
#include "MassNavigationTypes.h"
#include "StateTreeExecutionTypes.h"
#include "MassStateTreeExecutionContext.h"
#include "MassNavigationFragments.h"

EStateTreeRunStatus FEcsactIdle::EnterState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	UE_LOG(LogTemp, Log, TEXT("Entering Idle State"));

	// const auto& MassContext =
	// 	static_cast<FMassStateTreeExecutionContext&>(Context);

	// auto& MassSignalSubsystem =
	// 	Context.GetExternalData(MassSignalSubsystemHandle);
	//
	// MassSignalSubsystem.SignalEntity(
	// 	UE::Mass::Signals::StateTreeActivate,
	// 	MassContext.GetEntity()
	// );

	EStateTreeRunStatus Status = EStateTreeRunStatus::Running;

	auto& MoveTarget = Context.GetExternalData(MoveTargetHandle);

	if(MoveTarget.GetCurrentAction() == EMassMovementAction::Move) {
		UE_LOG(LogTemp, Error, TEXT("MASS MOVEMENT IS STILL MOVING"));
	}

	return Status;
}

void FEcsactIdle::ExitState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	UE_LOG(LogTemp, Log, TEXT("Exiting Idle State"));
}

// EStateTreeRunStatus FEcsactIdle::Tick(
// 	FStateTreeExecutionContext& Context,
// 	const float                 DeltaTime
// ) const {
// 	const auto& StreamingFragment =
// Context.GetExternalData(StreamFragmentHandle);
//
// 	// Assign this to a global tree parameter every single tick
// 	if(StreamingFragment.ShouldStream()) {
// 		return EStateTreeRunStatus::Succeeded;
// 	}
//
// 	return EStateTreeRunStatus::Running;
// }

bool FEcsactIdle::Link(FStateTreeLinker& Linker) {
	Linker.LinkExternalData(StreamFragmentHandle);
	Linker.LinkExternalData(MassSignalSubsystemHandle);
	Linker.LinkExternalData(MoveTargetHandle);
	return FMassStateTreeTaskBase::Link(Linker);
}
