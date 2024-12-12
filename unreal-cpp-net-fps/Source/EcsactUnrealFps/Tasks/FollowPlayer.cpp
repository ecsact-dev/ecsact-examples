
// Fill out your copyright notice in the Description page of Project Settings.
#include "FollowPlayer.h"

#include "MassCommonFragments.h"
#include "MassNavigationFragments.h"
#include "MassNavigationTypes.h"
#include "MassStateTreeTypes.h"
#include "MassStateTreeExecutionContext.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeLinker.h"

EStateTreeRunStatus FFollowPlayer::EnterState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	UE_LOG(LogTemp, Log, TEXT("Entering Follow Player State"));

	const auto& MassContext =
		static_cast<FMassStateTreeExecutionContext&>(Context);

	auto& MassSignalSubsystem =
		Context.GetExternalData(MassSignalSubsystemHandle);

	MassSignalSubsystem.SignalEntity(
		UE::Mass::Signals::StateTreeActivate,
		MassContext.GetEntity()
	);
	auto& MoveTarget = Context.GetExternalData(MoveTargetHandle);

	MoveTarget.CreateNewAction(EMassMovementAction::Move, *Context.GetWorld());
	MoveTarget.IntentAtGoal = EMassMovementAction::Move;
	MoveTarget.SlackRadius = 50.f;

	EStateTreeRunStatus Status = EStateTreeRunStatus::Running;
	MoveToPlayerPosition(Context);

	return Status;
}

void FFollowPlayer::ExitState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	UE_LOG(LogTemp, Log, TEXT("Exiting State"));
	auto& MoveTarget = Context.GetExternalData(MoveTargetHandle);

	MoveTarget = {};
	MoveTarget.CreateNewAction(EMassMovementAction::Stand, *Context.GetWorld());
	FMassStateTreeTaskBase::ExitState(Context, Transition);
}

EStateTreeRunStatus FFollowPlayer::Tick( //
	FStateTreeExecutionContext& Context,
	const float                 DeltaTime
) const {
	if(!Context.GetExternalData(StreamFragmentHandle).ShouldStream()) {
		return EStateTreeRunStatus::Running;
	}

	MoveToPlayerPosition(Context);

	return EStateTreeRunStatus::Running;
}

void FFollowPlayer::MoveToPlayerPosition( //
	FStateTreeExecutionContext& Context
) const {
	auto&              MoveTarget = Context.GetExternalData(MoveTargetHandle);
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	const auto& TransformFragment = Context.GetExternalData(TransformHandle);
	const auto& PlayerPosition = InstanceData.PlayerPosition;

	MoveTarget.Center = PlayerPosition;
	MoveTarget.Forward =
		(MoveTarget.Center - TransformFragment.GetTransform().GetLocation())
			.GetSafeNormal();
	MoveTarget.DistanceToGoal = FVector::Dist(
		MoveTarget.Center,
		TransformFragment.GetTransform().GetLocation()
	);
}

bool FFollowPlayer::Link(FStateTreeLinker& Linker) {
	Linker.LinkExternalData(StreamFragmentHandle);
	Linker.LinkExternalData(MoveTargetHandle);
	Linker.LinkExternalData(TransformHandle);
	Linker.LinkExternalData(MassSignalSubsystemHandle);
	return FMassStateTreeTaskBase::Link(Linker);
}
