#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "MassStateTreeTypes.h"
#include "StateTreeEvaluatorBase.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeLinker.h"
#include "MassSignalSubsystem.h"

#include "EcsactIdle.generated.h"

struct FMassMoveTargetFragment;

USTRUCT()

struct ECSACTUNREALFPS_API FEcsactIdleInstanceData {
	GENERATED_BODY() // nolint
};

USTRUCT()

struct ECSACTUNREALFPS_API FEcsactIdle : public FMassStateTreeTaskBase {
	GENERATED_BODY() // nolint
	//
	using FInstanceDataType = FEcsactIdleInstanceData;

	virtual const UStruct* GetInstanceDataType() const override {
		return FEcsactIdleInstanceData::StaticStruct();
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

	// virtual EStateTreeRunStatus Tick(
	// 	FStateTreeExecutionContext& Context,
	// 	const float                 DeltaTime
	// ) const override;

private:
	TStateTreeExternalDataHandle<UMassSignalSubsystem> MassSignalSubsystemHandle;
	TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;
};
