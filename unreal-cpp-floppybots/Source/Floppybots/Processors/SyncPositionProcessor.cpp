#include "SyncPositionProcessor.h"
#include "Floppybots/Fragments/EcsactFragments.h"
#include "Floppybots/Floppybots__ecsact__ue.h"
#include "Floppybots/Floppybots__ecsact__mass__ue.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "Floppybots/Fragments/LerpPositionFragment.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassRequirements.h"

USyncPositionProcessor::USyncPositionProcessor()
	: EntityQuery(*this) {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

auto USyncPositionProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;
	using EMassFragmentPresence::None;

	EntityQuery //
		.AddRequirement<FFloppybotsPositionFragment>(ReadOnly, All)
		.AddRequirement<FLerpPositionFragment>(ReadWrite, All)
		.AddTagRequirement<FEcsactStreamTag>(None);
}

auto USyncPositionProcessor::Execute(
	FMassEntityManager& EntityManager,
	FMassExecutionContext& Context
) -> void {
	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[](FMassExecutionContext& Context) {
			const auto num_entities = Context.GetNumEntities();

			auto pos_fragments =
				Context.GetFragmentView<FFloppybotsPositionFragment>();
			auto lerp_pos_fragments =
				Context.GetMutableFragmentView<FLerpPositionFragment>();

			for(auto i = 0; num_entities > i; ++i) {
				const auto entity_pos = pos_fragments[i].component;
				auto& lerp_pos = lerp_pos_fragments[i];
				lerp_pos.DesiredPosition = FVector{
					entity_pos.X,
					entity_pos.Y,
					entity_pos.Z,
				};
			}
		}
	);
}
