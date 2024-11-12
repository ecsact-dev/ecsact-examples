// Copyright Epic Games, Inc. All Rights Reserved.

#include "EcsactUnrealFpsPlayerController.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnrealFps/EcsactPlayerEntitySpawner.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AEcsactUnrealFpsPlayerController::BeginPlay() {
	Super::BeginPlay();

	// get the enhanced input subsystem
	auto* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			GetLocalPlayer()
		);
	if(Subsystem) {
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	auto runner = EcsactUnrealExecution::Runner(GetWorld()).Get();
	check(runner);
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

void AEcsactUnrealFpsPlayerController::BeginDestroy() {
	auto world = GetWorld();
	if(world) {
		auto runner = EcsactUnrealExecution::Runner(world).Get();
		if(runner) {
			auto player_spawner = runner->GetSubsystem<UEcsactPlayerEntitySpawner>();
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("AEcsactUnrealFpsPlayerController::BeginDestroy()")
			);
			if(player_spawner) {
				player_spawner->RemovePlayerController(this);
			}
		}
	}
	Super::BeginDestroy();
}
