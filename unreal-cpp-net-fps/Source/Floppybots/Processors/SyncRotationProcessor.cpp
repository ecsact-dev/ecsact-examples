#include "SyncRotationProcessor.h"
#include "Floppybots/Fragments/EcsactFragments.h"
#include "Floppybots/Floppybots__ecsact__ue.h"
#include "Floppybots/Floppybots__ecsact__mass__ue.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassRequirements.h"

USyncRotationProcessor::USyncRotationProcessor() : EntityQuery(*this) {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

auto USyncRotationProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;
	using EMassFragmentPresence::None;

	EntityQuery //
		.AddRequirement<FFloppybotsRotationFragment>(ReadOnly, All)
		.AddRequirement<FTransformFragment>(ReadWrite, All)
		.AddTagRequirement<FEcsactStreamTag>(None);
}

auto USyncRotationProcessor::Execute(
	FMassEntityManager&    EntityManager,
	FMassExecutionContext& Context
) -> void {
	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[](FMassExecutionContext& Context) {
			const auto num_entities = Context.GetNumEntities();

			auto rot_fragments =
				Context.GetFragmentView<FFloppybotsRotationFragment>();
			auto transform_fragments =
				Context.GetMutableFragmentView<FTransformFragment>();

			for(auto i = 0; num_entities > i; ++i) {
				auto ecsact_entity_rot = FVector{
					rot_fragments[i].component.Pitch,
					rot_fragments[i].component.Yaw,
					rot_fragments[i].component.Roll
				};
				auto& entity_transform = transform_fragments[i].GetMutableTransform();

				entity_transform.SetRotation(FQuat::MakeFromEuler(ecsact_entity_rot));
			}
		}
	);
}
