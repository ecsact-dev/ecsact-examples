#include "EnemyVisualProcessor.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"

UEnemyVisualProcessor::UEnemyVisualProcessor() {
}

auto UEnemyVisualProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentPresence::All;
	Super::ConfigureQueries();

	CloseEntityQuery.AddRequirement<FExampleEnemyFragment>(ReadOnly, All);
	FarEntityQuery.AddRequirement<FExampleEnemyFragment>(ReadOnly, All);
	DebugEntityQuery.AddRequirement<FExampleEnemyFragment>(ReadOnly, All);
	CloseEntityAdjustDistanceQuery.AddRequirement<FExampleEnemyFragment>(
		ReadOnly,
		All
	);
}

auto UEnemyRepresentationProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentPresence::All;
	Super::ConfigureQueries();

	EntityQuery.AddRequirement<FExampleEnemyFragment>(ReadOnly, All);
}
