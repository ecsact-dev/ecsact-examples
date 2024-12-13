#include "LerpPositionProcessor.h"
#include "EcsactUnrealFps/Fragments/LerpPositionFragment.h"
#include "EcsactUnrealFps/Fragments/LerpPositionParameters.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassRequirements.h"
#include "Math/UnrealMathUtility.h"

ULerpPositionProcessor::ULerpPositionProcessor() : EntityQuery(*this) {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

auto ULerpPositionProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;

	EntityQuery //
		.AddRequirement<FTransformFragment>(ReadWrite, All)
		.AddRequirement<FLerpPositionFragment>(ReadOnly, All)
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

				auto new_location = FMath::Lerp(
					transform.GetLocation(),
					lerp_pos.DesiredPosition,
					Context.GetDeltaTimeSeconds() * lerp_pos_params.Speed
				);

				transform.SetLocation(new_location);
			}
		}
	);
}
