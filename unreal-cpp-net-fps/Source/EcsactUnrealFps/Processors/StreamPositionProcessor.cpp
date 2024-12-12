#include "StreamPositionProcessor.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassRequirements.h"

UStreamPositionProcessor::UStreamPositionProcessor() {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

auto UStreamPositionProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;

	EntityQuery //
		.AddRequirement<FTransformFragment>(ReadOnly, All)
		.AddRequirement<FEcsactEntityFragment>(ReadOnly, All)
		.AddTagRequirement<FEcsactStreamTag>(All);

	RegisterQuery(EntityQuery);
}

auto UStreamPositionProcessor::Execute(
	FMassEntityManager&    EntityManager,
	FMassExecutionContext& Context
) -> void {
	auto runner = EcsactUnrealExecution::Runner(GetWorld()).Get();
	if(!runner) {
		return;
	}

	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[runner](FMassExecutionContext& Context) {
			const auto num_entities = Context.GetNumEntities();

			auto ecsact_entity_fragments =
				Context.GetFragmentView<FEcsactEntityFragment>();
			auto transform_fragments = Context.GetFragmentView<FTransformFragment>();

			for(auto i = 0; num_entities > i; ++i) {
				auto ecsact_entity = ecsact_entity_fragments[i].GetId();
				auto entity_loc = transform_fragments[i].GetTransform().GetLocation();
				runner->Stream(
					ecsact_entity,
					example::fps::Position{
						.x = static_cast<float>(entity_loc.X),
						.y = static_cast<float>(entity_loc.Y),
						.z = static_cast<float>(entity_loc.Z),
					}
				);
			}
		}
	);
}
