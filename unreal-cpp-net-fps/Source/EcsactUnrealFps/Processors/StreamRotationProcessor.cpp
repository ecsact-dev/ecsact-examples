#include "StreamRotationProcessor.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__mass__ue.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassRequirements.h"

UStreamRotationProcessor::UStreamRotationProcessor() : EntityQuery(*this) {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

auto UStreamRotationProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;

	EntityQuery //
		.AddRequirement<FTransformFragment>(ReadOnly, All)
		.AddRequirement<FEcsactEntityFragment>(ReadOnly, All)
		.AddTagRequirement<FEcsactStreamTag>(All);
}

auto UStreamRotationProcessor::Execute(
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
				auto entity_rot =
					transform_fragments[i].GetTransform().GetRotation().Euler();

				runner->Stream(
					ecsact_entity,
					example::fps::Rotation{
						.pitch = static_cast<float>(entity_rot.Y),
						.yaw = static_cast<float>(entity_rot.Z),
						.roll = static_cast<float>(entity_rot.X),
					}
				);
			}
		}
	);
}
