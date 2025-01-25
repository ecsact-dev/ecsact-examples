#include "LerpPositionProcessor.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "EcsactUnrealFps/Fragments/LerpPositionFragment.h"
#include "EcsactUnrealFps/Fragments/LerpPositionParameters.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassRequirements.h"
#include "Math/UnrealMathUtility.h"

ULerpPositionProcessor::ULerpPositionProcessor() : EntityQuery(*this) {
	ProcessingPhase = EMassProcessingPhase::PrePhysics;
}

auto ULerpPositionProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;
	using EMassFragmentPresence::None;

	EntityQuery //
		.AddRequirement<FTransformFragment>(ReadWrite, All)
		.AddRequirement<FLerpPositionFragment>(ReadOnly, All)
		.AddTagRequirement<FEcsactStreamTag>(None)
		.AddConstSharedRequirement<FLerpPositionParameters>(All);
}

auto ULerpPositionProcessor::Execute(
	FMassEntityManager&    EntityManager,
	FMassExecutionContext& Context
) -> void {
	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[](FMassExecutionContext& Context) {
			const auto num_entities = Context.GetNumEntities();

			auto transform_fragments =
				Context.GetMutableFragmentView<FTransformFragment>();
			auto lerp_pos_fragments =
				Context.GetFragmentView<FLerpPositionFragment>();

			const auto& lerp_pos_params =
				Context.GetConstSharedFragment<FLerpPositionParameters>();

			for(auto i = 0; num_entities > i; ++i) {
				auto& transform = transform_fragments[i].GetMutableTransform();
				auto  lerp_pos = lerp_pos_fragments[i];

				if(lerp_pos_params.Disabled) {
					transform.SetLocation(lerp_pos.DesiredPosition);
				} else {
					auto new_location = FMath::Lerp(
						transform.GetLocation(),
						lerp_pos.DesiredPosition,
						Context.GetDeltaTimeSeconds() * lerp_pos_params.Speed
					);

					transform.SetLocation(new_location);
				}
			}
		}
	);
}
