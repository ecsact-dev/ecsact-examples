#include "LerpPositionTrait.h"
#include "MassEntityUtils.h"
#include "Floppybots/Fragments/LerpPositionFragment.h"
#include "MassEntityTemplateRegistry.h"

auto ULerpPositionTrait::BuildTemplate( //
	FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World
) const -> void {
	auto& entity_manager = UE::Mass::Utils::GetEntityManagerChecked(World);

	BuildContext.AddFragment<FLerpPositionFragment>();
	BuildContext.AddConstSharedFragment(
		entity_manager.GetOrCreateConstSharedFragment(PositionParameters)
	);
}
