#include "EnemyVisualProcessor.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"

UEnemyVisualProcessor::UEnemyVisualProcessor() {
}

auto UEnemyVisualProcessor::ConfigureQueries() -> void {
	using EMassFragmentPresence::All;
	Super::ConfigureQueries();

	CloseEntityQuery.AddTagRequirement<FExampleEnemyTag>(All);
	FarEntityQuery.AddTagRequirement<FExampleEnemyTag>(All);
	DebugEntityQuery.AddTagRequirement<FExampleEnemyTag>(All);
	CloseEntityAdjustDistanceQuery.AddTagRequirement<FExampleEnemyTag>(All);
}

auto UEnemyRepresentationProcessor::ConfigureQueries() -> void {
	using EMassFragmentPresence::All;
	Super::ConfigureQueries();

	EntityQuery.AddTagRequirement<FExampleEnemyTag>(All);
}
