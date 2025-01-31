#include "EnemyVisualProcessor.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__mass__ue.h"

UEnemyVisualProcessor::UEnemyVisualProcessor() {
}

auto UEnemyVisualProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentPresence::All;
	Super::ConfigureQueries();

	CloseEntityQuery.AddRequirement<FExampleFpsEnemyFragment>(ReadOnly, All);
	FarEntityQuery.AddRequirement<FExampleFpsEnemyFragment>(ReadOnly, All);
	DebugEntityQuery.AddRequirement<FExampleFpsEnemyFragment>(ReadOnly, All);
	CloseEntityAdjustDistanceQuery.AddRequirement<FExampleFpsEnemyFragment>(
		ReadOnly,
		All
	);
}

auto UEnemyRepresentationProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentPresence::All;
	Super::ConfigureQueries();

	EntityQuery.AddRequirement<FExampleFpsEnemyFragment>(ReadOnly, All);
}
