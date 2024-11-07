#include "TickProcessor.h"
#include "MassArchetypeTypes.h"
#include "MassRequirements.h"
#include "MassSignalSubsystem.h"
#include "MassStateTreeFragments.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "MassStateTreeTypes.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "../Fragments/EcsactFragments.h"
#include "../EcsactUnrealFps.ecsact.hh"
#include "UObject/UnrealNames.h"

void UTickProcessor::ConfigureQueries() {
	EntityQuery.AddSubsystemRequirement<UMassSignalSubsystem>(
		EMassFragmentAccess::ReadWrite
	);
	EntityQuery.RegisterWithProcessor(*this);
	EntityQuery.AddRequirement<FMassStateTreeInstanceFragment>(
		EMassFragmentAccess::None
	);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite
	);
	EntityQuery.AddRequirement<FEcsactEntityFragment>(
		EMassFragmentAccess::ReadOnly
	);
	EntityQuery.AddRequirement<FEcsactPositionFragment>(
		EMassFragmentAccess::ReadOnly
	);
	EntityQuery.AddRequirement<FEcsactStreamFragment>(
		EMassFragmentAccess::ReadOnly
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

			auto runner = EcsactUnrealExecution::Runner();
			if(!runner.IsValid()) {
				return;
			}

			const auto& StreamFragments =
				Context.GetFragmentView<FEcsactStreamFragment>();

			const auto& EntityFragments =
				Context.GetFragmentView<FEcsactEntityFragment>();

			auto TransformFragments =
				Context.GetMutableFragmentView<FTransformFragment>();
			const auto& PositionFragments =
				Context.GetFragmentView<FEcsactPositionFragment>();

			for(int i = 0; i < TransformFragments.Num(); ++i) {
				const bool ShouldStream = StreamFragments[i].ShouldStream();

				if(ShouldStream) {
					const auto& TransformLoc =
						TransformFragments[i].GetTransform().GetLocation();
					const auto& Entity = EntityFragments[i].GetId();

					runner->Stream(
						Entity,
						example::fps::Position{
							.x = static_cast<float>(TransformLoc.X),
							.y = static_cast<float>(TransformLoc.Y),
							.z = static_cast<float>(TransformLoc.Z),
						}
					);
				} else {
					UE_LOG(LogTemp, Log, TEXT("Stream turned off!"));

					auto&       Transform = TransformFragments[i];
					const auto& Position = PositionFragments[i].GetPosition();

					Transform.SetTransform(FTransform{Position});
				}
			}
		}
	);
}