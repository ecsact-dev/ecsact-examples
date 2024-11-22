#include "EcsactUnrealFpsPlayerController.h"

#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnrealFps/EcsactPlayerEntitySpawner.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AEcsactUnrealFpsPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto runner = EcsactUnrealExecution::RunnerOrWarn(GetWorld()).Get();
	if(!runner) {
		UE_LOG(LogTemp, Warning, TEXT("NO RUNNER??????????????"));
		return;
	}

	// get the enhanced input subsystem
	auto* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			GetLocalPlayer()
		);
	if(Subsystem) {
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	auto player_spawner = runner->GetSubsystem<UEcsactPlayerEntitySpawner>();
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("AEcsactUnrealFpsPlayerController::BeginPlay()")
	);
	if(player_spawner) {
		player_spawner->AddPlayerController(this);
	} else {
		UE_LOG(LogTemp, Error, TEXT("Player Spawner is not ready"));
	}
}

void AEcsactUnrealFpsPlayerController::EndPlay( //
	const EEndPlayReason::Type Reason
) {
	switch(Reason) {
		case EEndPlayReason::EndPlayInEditor:
		case EEndPlayReason::Quit:
			Super::EndPlay(Reason);
			return;
		case EEndPlayReason::Destroyed:
		case EEndPlayReason::LevelTransition:
		case EEndPlayReason::RemovedFromWorld:
			break;
	}

	auto runner = EcsactUnrealExecution::RunnerOrWarn(GetWorld()).Get();
	if(runner) {
		auto player_spawner = runner->GetSubsystem<UEcsactPlayerEntitySpawner>();
		if(player_spawner) {
			player_spawner->RemovePlayerController(this);
		}
	}
	Super::EndPlay(Reason);
}
