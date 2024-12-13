#include "SyncPositionProcessor.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnrealFps/Fragments/LerpPositionFragment.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassRequirements.h"

USyncPositionProcessor::USyncPositionProcessor() {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

auto USyncPositionProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;
	using EMassFragmentPresence::None;

	EntityQuery //
		.AddRequirement<FEcsactPositionFragment>(ReadOnly, All)
		.AddRequirement<FLerpPositionFragment>(ReadWrite, All)
		.AddTagRequirement<FEcsactStreamTag>(None);

	RegisterQuery(EntityQuery);
}

auto USyncPositionProcessor::Execute(
	FMassEntityManager&    EntityManager,
	FMassExecutionContext& Context
) -> void {
	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[](FMassExecutionContext& Context) {
			const auto num_entities = Context.GetNumEntities();

			auto pos_fragments = Context.GetFragmentView<FEcsactPositionFragment>();
			auto lerp_pos_fragments =
				Context.GetMutableFragmentView<FLerpPositionFragment>();

			for(auto i = 0; num_entities > i; ++i) {
				auto  entity_pos = pos_fragments[i].GetPosition();
				auto& lerp_pos = lerp_pos_fragments[i];
				lerp_pos.DesiredPosition =
					FVector{entity_pos.X, entity_pos.Y, entity_pos.Z};
			}
		}
	);
}
