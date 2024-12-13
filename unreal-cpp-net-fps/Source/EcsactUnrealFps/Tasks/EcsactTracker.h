
#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "MassSignalSubsystem.h"
#include "MassStateTreeTypes.h"
#include "MassStateTreeTypes.h"
#include "StateTreeEvaluatorBase.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeExecutionTypes.h"

#include "EcsactTracker.generated.h"

USTRUCT()

struct ECSACTUNREALFPS_API FEcsactTrackerInstanceData {
	GENERATED_BODY() // nolint
	UPROPERTY(EditAnywhere, Category = Output) bool bIsStreaming = false;
	UPROPERTY(VisibleAnywhere, Category = Output) FVector PlayerPosition;
};

USTRUCT()

struct ECSACTUNREALFPS_API FEcsactTracker : public FMassStateTreeTaskBase {
	GENERATED_BODY() // nolint

	FEcsactTracker();

	using FInstanceDataType = FEcsactTrackerInstanceData;

	virtual const UStruct* GetInstanceDataType() const override {
		return FEcsactTrackerInstanceData::StaticStruct();
	}

	virtual bool Link(FStateTreeLinker& Linker) override;

	virtual EStateTreeRunStatus EnterState(
		FStateTreeExecutionContext&       Context,
		const FStateTreeTransitionResult& Transition
	) const override;

	virtual EStateTreeRunStatus Tick(
		FStateTreeExecutionContext& Context,
		const float                 DeltaTime
	) const override;
};
