// Copyright Epic Games, Inc. All Rights Reserved.

#include "EcsactUnrealFpsGameMode.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "EcsactUnrealFpsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "ecsact/runtime/async.h"

AEcsactUnrealFpsGameMode::AEcsactUnrealFpsGameMode() : Super() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/Blueprints/BP_FirstPersonCharacter")
	);
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

auto AEcsactUnrealFpsGameMode::ShouldSpawnAtStartSpot( //
	AController* Controller
) -> bool {
	return false;
}

auto AEcsactUnrealFpsGameMode::HandleStartingNewPlayer_Implementation( //
	APlayerController* NewPlayer
) -> void {
	// NOTE: UEcsactEntityPlayerSpawner is responsible for spawning the pawn
	// Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}
