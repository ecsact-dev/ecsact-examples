#include "EnemyVisualProcessor.h"
#include "Floppybots/Floppybots__ecsact__mass__ue.h"

UEnemyVisualProcessor::UEnemyVisualProcessor() {
}

auto UEnemyVisualProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentPresence::All;
	Super::ConfigureQueries();

	// Only use the mass visualizer on Ecsact entities with the 'Enemy' component
	CloseEntityQuery.AddRequirement<FFloppybotsEnemyFragment>(ReadOnly, All);
	FarEntityQuery.AddRequirement<FFloppybotsEnemyFragment>(ReadOnly, All);
	DebugEntityQuery.AddRequirement<FFloppybotsEnemyFragment>(ReadOnly, All);
	CloseEntityAdjustDistanceQuery.AddRequirement<FFloppybotsEnemyFragment>(
		ReadOnly,
		All
	);
}

auto UEnemyRepresentationProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentPresence::All;
	Super::ConfigureQueries();

	EntityQuery.AddRequirement<FFloppybotsEnemyFragment>(ReadOnly, All);
}
