#include "FollowPlayerProcessor.h"
#include "Floppybots/Fragments/EcsactFragments.h"
#include "Floppybots/Floppybots__ecsact__ue.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "Floppybots/Fragments/FollowPlayerTargetFragment.h"
#include "Floppybots/Fragments/LerpPositionFragment.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassNavigationFragments.h"
#include "MassNavigationTypes.h"
#include "MassRequirements.h"

UFollowPlayerProcessor::UFollowPlayerProcessor()
	: EntityQuery(*this) {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

auto UFollowPlayerProcessor::ConfigureQueries() -> void {
	using EMassFragmentAccess::ReadOnly;
	using EMassFragmentAccess::ReadWrite;
	using EMassFragmentPresence::All;
	using EMassFragmentPresence::None;

	EntityQuery //
		.AddRequirement<FTransformFragment>(ReadOnly, All)
		.AddRequirement<FMassMoveTargetFragment>(ReadWrite, All)
		.AddSharedRequirement<FFollowPlayerTargetFragment>(ReadOnly, All)
		.AddTagRequirement<FEcsactStreamTag>(All);
}

auto UFollowPlayerProcessor::Execute(
	FMassEntityManager& EntityManager,
	FMassExecutionContext& Context
) -> void {
	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[](FMassExecutionContext& Context) {
			const auto num_entities = Context.GetNumEntities();

			auto transform_fragments = Context.GetFragmentView<FTransformFragment>();
			auto move_target_fragments =
				Context.GetMutableFragmentView<FMassMoveTargetFragment>();

			const auto& follow_player_target =
				Context.GetSharedFragment<FFollowPlayerTargetFragment>();

			for(auto i = 0; num_entities > i; ++i) {
				auto& move_target = move_target_fragments[i];
				const auto& transform = transform_fragments[i].GetTransform();
				auto entity_loc = transform.GetLocation();
				const auto closest_player_pos =
					follow_player_target.GetClosestPlayerPosition(entity_loc);

				move_target.CreateNewAction(
					EMassMovementAction::Move,
					*Context.GetWorld()
				);
				move_target.IntentAtGoal = EMassMovementAction::Move;
				move_target.SlackRadius = 50.f;
				move_target.Center = closest_player_pos;
				move_target.Center.Z = 0.0f;
				move_target.Forward = (move_target.Center - entity_loc).GetSafeNormal();
				move_target.DistanceToGoal =
					FVector::Dist(move_target.Center, entity_loc);
			}
		}
	);
}
