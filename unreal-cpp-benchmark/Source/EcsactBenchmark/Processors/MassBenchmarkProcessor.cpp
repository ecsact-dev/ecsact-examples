#include "MassBenchmarkProcessor.h"
#include "../EcsactBenchmark__ecsact__mass__ue.h"
#include "EcsactBenchmark/EcsactBenchmark__ecsact__ue.h"
#include "MassArchetypeTypes.h"

#include "../Fragments/MassCounterFragments.h"
#include "MassEntityView.h"
#include "MassExecutionContext.h"
#include "MassRequirements.h"

UMassBenchmarkProcessor::UMassBenchmarkProcessor() : EntityQuery(*this) {
}

void UMassBenchmarkProcessor::ConfigureQueries() {
	EntityQuery.AddRequirement<FBenchmarkCounterFragment>(
		EMassFragmentAccess::ReadWrite
	);
	EntityQuery.AddTagRequirement<FRunMassCounter>(EMassFragmentPresence::All);
}

void UMassBenchmarkProcessor::Execute(
	FMassEntityManager&    EntityManager,
	FMassExecutionContext& Context
) {
	EntityQuery.ForEachEntityChunk( //
		EntityManager,
		Context,
		[](FMassExecutionContext& context) {
			const auto entity_num = context.GetNumEntities();
			auto       counter_fragments =
				context.GetMutableFragmentView<FBenchmarkCounterFragment>();

			for(int i = 0; i < entity_num; ++i) {
				auto& counter_fragment = counter_fragments[i];

				counter_fragment.component.Value += 1;

				// UE_LOG(
				// 	LogTemp,
				// 	Warning,
				// 	TEXT("MASS: Updated entity counter to %i"),
				// 	counter_fragment.component.Value
				// );
			}
		}
	);
}
