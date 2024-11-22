
#include "EcsactTraits.h"
#include "MassEntityTemplateRegistry.h"
#include "MassEntityUtils.h"

void UEcsactStreamingTrait::BuildTemplate(
	FMassEntityTemplateBuildContext& BuildContext,
	const UWorld&                    World
) const {
	FMassEntityManager& EntityManager =
		UE::Mass::Utils::GetEntityManagerChecked(World);

	const auto StreamingFragment =
		EntityManager.GetOrCreateConstSharedFragment(Streaming);

	BuildContext.AddConstSharedFragment(StreamingFragment);
}
