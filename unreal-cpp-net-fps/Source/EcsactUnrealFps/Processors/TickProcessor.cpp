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

			auto Entities = Context.GetEntities();
			SignalSubsystem.SignalEntities(
				UE::Mass::Signals::StateTreeActivate,
				Entities
			);

			const auto NumEntities = Context.GetNumEntities();
			auto StreamFragments = Context.GetFragmentView<FEcsactStreamFragment>();
			auto EntityFragments = Context.GetFragmentView<FEcsactEntityFragment>();
			auto TransformFragments =
				Context.GetMutableFragmentView<FTransformFragment>();
			auto PositionFragments =
				Context.GetFragmentView<FEcsactPositionFragment>();

			for(int32 i = 0; NumEntities > i; ++i) {
				const bool ShouldStream = StreamFragments[i].ShouldStream();

				if(ShouldStream) {
					auto TransformLoc =
						TransformFragments[i].GetTransform().GetLocation();
					auto Entity = EntityFragments[i].GetId();

					runner->Stream(
						Entity,
						example::fps::Position{
							.x = static_cast<float>(TransformLoc.X),
							.y = static_cast<float>(TransformLoc.Y),
							.z = static_cast<float>(TransformLoc.Z),
						}
					);
				} else {
					auto& Transform = TransformFragments[i].GetMutableTransform();
					auto  Position = PositionFragments[i].GetPosition();

					// const auto& Location = Transform.GetLocation();

					// UE_LOG(
					// 	LogTemp,
					// 	Log,
					// 	TEXT("Current transform location of entity %i: %f, %f, %f"),
					// 	i,
					// 	Location.X,
					// 	Location.Y,
					// 	Location.Z
					// );

					// UE_LOG(
					// 	LogTemp,
					// 	Log,
					// 	TEXT("Setting position to entity %i: %f, %f, %f"),
					// 	i,
					// 	Position.X,
					// 	Position.Y,
					// 	Position.Z
					// );

					Transform.SetLocation(Position);
				}
			}
		}
	);
}
