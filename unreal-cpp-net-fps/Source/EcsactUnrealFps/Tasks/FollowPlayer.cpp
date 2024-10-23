
// Fill out your copyright notice in the Description page of Project Settings.
#include "FollowPlayer.h"

#include "MassCommonFragments.h"
#include "MassNavigationFragments.h"
#include "MassNavigationTypes.h"
#include "MassStateTreeTypes.h"
#include "MassStateTreeExecutionContext.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeLinker.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnrealFps/EcsactPlayerEntitySpawner.h"
#include "EcsactUnreal/EcsactRunner.h"

EStateTreeRunStatus FFollowPlayer::EnterState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	UE_LOG(LogTemp, Log, TEXT("Entering State"));

	const auto& MassContext =
		static_cast<FMassStateTreeExecutionContext&>(Context);

	auto& MassSignalSubsystem =
		Context.GetExternalData(MassSignalSubsystemHandle);

	MassSignalSubsystem.SignalEntity(
		UE::Mass::Signals::StateTreeActivate,
		MassContext.GetEntity()
	);

	EStateTreeRunStatus Status = EStateTreeRunStatus::Running;
	MoveToPlayerPosition(Context);

	return Status;
}

void FFollowPlayer::ExitState(
	FStateTreeExecutionContext&       Context,
	const FStateTreeTransitionResult& Transition
) const {
	UE_LOG(LogTemp, Log, TEXT("Exiting State"));

	FMassStateTreeTaskBase::ExitState(Context, Transition);
}

EStateTreeRunStatus FFollowPlayer::Tick( //
	FStateTreeExecutionContext& Context,
	const float                 DeltaTime
) const {
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	MoveToPlayerPosition(Context);

	return EStateTreeRunStatus::Running;
}

void FFollowPlayer::MoveToPlayerPosition(FStateTreeExecutionContext& Context
) const {
	auto runner = EcsactUnrealExecution::Runner();
	check(runner.IsValid());
	auto PlayerSpawner = runner->GetSubsystem<UEcsactPlayerEntitySpawner>();
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

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

	auto&       MoveTarget = Context.GetExternalData(MoveTargetHandle);
	const auto& TransformFragment = Context.GetExternalData(TransformHandle);
	const auto& PlayerPosition = InstanceData.PlayerPosition;
	UE_LOG(
		LogTemp,
		Log,
		TEXT("Move to Position %f %f %f"),
		PlayerPosition.X,
		PlayerPosition.Y,
		PlayerPosition.Z
	);

	MoveTarget.Center = PlayerPosition;
	MoveTarget.SlackRadius = 50.f;
	MoveTarget.Forward =
		(MoveTarget.Center - TransformFragment.GetTransform().GetLocation())
			.GetSafeNormal();
	MoveTarget.DistanceToGoal = FVector::Dist(
		MoveTarget.Center,
		TransformFragment.GetTransform().GetLocation()
	);

	MoveTarget.CreateNewAction(EMassMovementAction::Move, *Context.GetWorld());
	MoveTarget.IntentAtGoal = EMassMovementAction::Stand;
}

bool FFollowPlayer::Link(FStateTreeLinker& Linker) {
	Linker.LinkExternalData(MoveTargetHandle);
	Linker.LinkExternalData(TransformHandle);
	Linker.LinkExternalData(MassSignalSubsystemHandle);
	return FMassStateTreeTaskBase::Link(Linker);
}
