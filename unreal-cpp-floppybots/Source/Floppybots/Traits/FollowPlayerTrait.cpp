#include "FollowPlayerTrait.h"
#include "Floppybots/Fragments/FollowPlayerTargetFragment.h"
#include "MassCommonFragments.h"
#include "MassEntityUtils.h"
#include "MassEntityTemplateRegistry.h"
#include "MassNavigationFragments.h"

auto UFollowPlayerTrait::BuildTemplate( //
	FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World
) const -> void {
	auto& entity_manager = UE::Mass::Utils::GetEntityManagerChecked(World);
	BuildContext.RequireFragment<FMassMoveTargetFragment>();
	BuildContext.RequireFragment<FTransformFragment>();
	BuildContext.AddSharedFragment(
		entity_manager.GetOrCreateSharedFragmentByHash<FFollowPlayerTargetFragment>(
			UE::StructUtils::GetStructCrc32(
				FConstStructView::Make(FFollowPlayerTargetFragment{})
			)
		)
	);
}
