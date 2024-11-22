#include "EcsactIdle.h"
#include "StateTreeExecutionTypes.h"
#include "MassStateTreeExecutionContext.h"

EStateTreeRunStatus FEcsactIdle::EnterState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	UE_LOG(LogTemp, Log, TEXT("Entering Idle State"));

	const auto& MassContext =
		static_cast<FMassStateTreeExecutionContext&>(Context);

	auto& MassSignalSubsystem =
		Context.GetExternalData(MassSignalSubsystemHandle);

	MassSignalSubsystem.SignalEntity(
		UE::Mass::Signals::StateTreeActivate,
		MassContext.GetEntity()
	);

	EStateTreeRunStatus Status = EStateTreeRunStatus::Running;

	return Status;
}

void FEcsactIdle::ExitState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	UE_LOG(LogTemp, Log, TEXT("Exiting Idle State"));
}

EStateTreeRunStatus FEcsactIdle::Tick(
	FStateTreeExecutionContext& Context,
	const float                 DeltaTime
) const {
	const auto& StreamingFragment = Context.GetExternalData(StreamFragmentHandle);

	if(StreamingFragment.ShouldStream()) {
		return EStateTreeRunStatus::Succeeded;
	}

	return EStateTreeRunStatus::Running;
}

bool FEcsactIdle::Link(FStateTreeLinker& Linker) {
	Linker.LinkExternalData(StreamFragmentHandle);
	Linker.LinkExternalData(MassSignalSubsystemHandle);
	return FMassStateTreeTaskBase::Link(Linker);
}
