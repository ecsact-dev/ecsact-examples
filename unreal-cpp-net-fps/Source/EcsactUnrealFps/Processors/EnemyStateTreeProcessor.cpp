#include "EnemyStateTreeProcessor.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassSignalSubsystem.h"
#include "MassRequirements.h"
#include "MassStateTreeFragments.h"
#include "MassStateTreeTypes.h"

UEnemyStateTreeProcessor::UEnemyStateTreeProcessor() : EntityQuery(*this) {
}

auto UEnemyStateTreeProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;
	using EMassFragmentPresence::None;

	EntityQuery.AddSubsystemRequirement<UMassSignalSubsystem>(ReadWrite);
	EntityQuery //
		.AddRequirement<FMassStateTreeInstanceFragment>(ReadWrite, All)
		.AddTagRequirement<FEcsactStreamTag>(None);
}

auto UEnemyStateTreeProcessor::Execute(
	FMassEntityManager&    EntityManager,
	FMassExecutionContext& Context
) -> void {
	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[](FMassExecutionContext& Context) {
			auto& mass_signal =
				Context.GetMutableSubsystemChecked<UMassSignalSubsystem>();

			mass_signal.SignalEntities(
				UE::Mass::Signals::StateTreeActivate,
				Context.GetEntities()
			);
		}
	);
}
