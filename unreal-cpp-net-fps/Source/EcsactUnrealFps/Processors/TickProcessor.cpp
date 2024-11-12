#include "TickProcessor.h"
#include "MassArchetypeTypes.h"
#include "MassProcessingTypes.h"
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

UTickProcessor::UTickProcessor() {
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

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
	auto runner = EcsactUnrealExecution::Runner(GetWorld()).Get();
	if(!runner) {
		return;
	}

	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[runner](FMassExecutionContext& Context) {
			UMassSignalSubsystem& SignalSubsystem =
				Context.GetMutableSubsystemChecked<UMassSignalSubsystem>();

			const auto& Entities = Context.GetEntities();
			SignalSubsystem.SignalEntities(
				UE::Mass::Signals::StateTreeActivate,
				Entities
			);

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
					// UE_LOG(LogTemp, Log, TEXT("Streaming mass entity"));
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
					auto&       Transform = TransformFragments[i].GetMutableTransform();
					const auto& Position = PositionFragments[i].GetPosition();

					const auto& Location = Transform.GetLocation();

					// UE_LOG(
					// 	LogTemp,
					// 	Log,
					// 	TEXT("Current transform location of entity %i: %f, %f, %f"),
					// 	i,
					// 	Location.X,
					// 	Location.Y,
					// 	Location.Z
					// );
					//
					// UE_LOG(
					// 	LogTemp,
					// 	Log,
					// 	TEXT("Setting position to entity %i: %f, %f, %f"),
					// 	i,
					// 	Position.X,
					// 	Position.Y,
					// 	Position.Z
					// );

					Transform.SetLocation(FVector{Position});
				}
			}
		}
	);
}
