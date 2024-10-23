
#pragma once

#include "CoreMinimal.h"
#include "MassStateTreeTypes.h"
#include "StateTreeEvaluatorBase.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeExecutionTypes.h"
#include "Engine/TimerHandle.h"
#include "MassSignalSubsystem.h"

#include "FollowPlayer.generated.h"

struct FTransformFragment;
struct FMassMoveTargetFragment;

USTRUCT()

struct ECSACTUNREALFPS_API FFollowPlayerInstanceData {
	GENERATED_BODY() // nolint
	UPROPERTY(EditAnywhere, Category = Parameter) FVector PlayerPosition;
};

USTRUCT()

struct ECSACTUNREALFPS_API FFollowPlayer : public FMassStateTreeTaskBase {
	GENERATED_BODY() // nolint

	using FInstanceDataType = FFollowPlayerInstanceData;

	virtual const UStruct* GetInstanceDataType() const override {
		return FFollowPlayerInstanceData::StaticStruct();
	}

	virtual bool Link(FStateTreeLinker& Linker) override;

	virtual EStateTreeRunStatus EnterState(
		FStateTreeExecutionContext&       Context,
		const FStateTreeTransitionResult& Transition
	) const override;

	virtual void ExitState(
		FStateTreeExecutionContext&       Context,
		const FStateTreeTransitionResult& Transition
	) const override;

	virtual EStateTreeRunStatus Tick(
		FStateTreeExecutionContext& Context,
		const float                 DeltaTime
	) const override;

	void MoveToPlayerPosition(FStateTreeExecutionContext& Context) const;

private:
	TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;
	TStateTreeExternalDataHandle<FTransformFragment>      TransformHandle;
	TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;

	void OnWaitComplete();
};
