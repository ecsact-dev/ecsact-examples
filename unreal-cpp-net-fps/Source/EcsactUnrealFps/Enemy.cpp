#include "Enemy.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__mass__ue.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"
#include "MassCommandBuffer.h"
#include "MassEntitySubsystem.h"
#include "MassActorSubsystem.h"
#include "MassEntityManager.h"
#include "MassCommands.h"

AEnemy::AEnemy() {
}

void AEnemy::BeginPlay() {
	Super::BeginPlay();

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	// NOTE: entity handle is not valid in BeginPlay so we must defer
	entity_manager.Defer().PushCommand<FMassDeferredSetCommand>(
		[this](FMassEntityManager& entity_manager) {
			auto world = entity_manager.GetWorld();
			auto mass_actor_subsystem = world->GetSubsystem<UMassActorSubsystem>();
			auto entity_handle = mass_actor_subsystem->GetEntityHandleFromActor(this);

			if(entity_handle.IsValid()) {
				auto enemy_fragment =
					entity_manager.GetFragmentDataPtr<FExampleFpsEnemyFragment>(
						entity_handle
					);
				if(enemy_fragment) {
					OnInitEnemy(FExampleFpsEnemy{enemy_fragment->component});
				} else {
					UE_LOG(LogTemp, Warning, TEXT("No enemy fragment!"));
				}
			} else {
				UE_LOG(LogTemp, Warning, TEXT("Enemy invalid entity handle"));
			}
		}
	);
}
