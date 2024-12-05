
#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "MassStateTreeTypes.h"
#include "StateTreeEvaluatorBase.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeExecutionTypes.h"

#include "EcsactTracker.generated.h"

USTRUCT()

struct ECSACTUNREALFPS_API FEcsactTrackerInstanceData {
	GENERATED_BODY() // nolint
	UPROPERTY(VisibleAnywhere, Category = Output) bool bIsStreaming = false;
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

	virtual EStateTreeRunStatus Tick(
		FStateTreeExecutionContext& Context,
		const float                 DeltaTime
	) const override;

private:
	TStateTreeExternalDataHandle<FEcsactStreamFragment> StreamFragmentHandle;
};
