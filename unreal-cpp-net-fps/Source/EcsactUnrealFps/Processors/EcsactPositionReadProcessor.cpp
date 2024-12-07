#include "EcsactPositionReadProcessor.h"

#include "MassArchetypeTypes.h"
#include "MassProcessingTypes.h"
#include "MassRequirements.h"
#include "MassSignalSubsystem.h"
#include "MassStateTreeFragments.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassStateTreeTypes.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "../Fragments/EcsactFragments.h"

UEcsactPositionReadProcessor::UEcsactPositionReadProcessor() {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

void UEcsactPositionReadProcessor::ConfigureQueries() {
	EntityQuery.AddSubsystemRequirement<UMassSignalSubsystem>(
		EMassFragmentAccess::ReadWrite
	);
	EntityQuery.RegisterWithProcessor(*this);
	EntityQuery.AddRequirement<FMassStateTreeInstanceFragment>(
		EMassFragmentAccess::None
	);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite
	);
	EntityQuery.AddRequirement<FEcsactEntityFragment>(
		EMassFragmentAccess::ReadOnly
	);
	EntityQuery.AddRequirement<FEcsactPositionFragment>(
		EMassFragmentAccess::ReadOnly
	);
	EntityQuery.AddRequirement<FEcsactStreamFragment>(
		EMassFragmentAccess::ReadOnly
	);
}

void UEcsactPositionReadProcessor::Execute(
	FMassEntityManager&    EntityManager,
	FMassExecutionContext& Context
) {
}
