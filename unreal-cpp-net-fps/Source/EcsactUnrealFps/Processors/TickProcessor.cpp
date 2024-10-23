#include "TickProcessor.h"
#include "MassArchetypeTypes.h"
#include "MassRequirements.h"
#include "MassSignalSubsystem.h"
#include "MassStateTreeFragments.h"
#include "MassExecutionContext.h"
#include "MassStateTreeTypes.h"

void UTickProcessor::ConfigureQueries() {
	EntityQuery.AddSubsystemRequirement<UMassSignalSubsystem>(
		EMassFragmentAccess::ReadWrite
	);
	EntityQuery.RegisterWithProcessor(*this);
	EntityQuery.AddRequirement<FMassStateTreeInstanceFragment>(
		EMassFragmentAccess::None
	);
}

void UTickProcessor::Execute(
	FMassEntityManager&    EntityManager,
	FMassExecutionContext& Context
) {
	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[](FMassExecutionContext& Context) {
			UMassSignalSubsystem& SignalSubsystem =
				Context.GetMutableSubsystemChecked<UMassSignalSubsystem>();

			const auto& Entities = Context.GetEntities();
			SignalSubsystem.SignalEntities(
				UE::Mass::Signals::StateTreeActivate,
				Entities
			);
		}
	);
}
