// Copyright Epic Games, Inc. All Rights Reserved.

#include "FloppybotsGameMode.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "FloppybotsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "ecsact/runtime/async.h"

AFloppybotsGameMode::AFloppybotsGameMode()
	: Super() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/Blueprints/BP_FirstPersonCharacter")
	);
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

auto AFloppybotsGameMode::ShouldSpawnAtStartSpot( //
	AController* Controller
) -> bool {
	return false;
}

auto AFloppybotsGameMode::HandleStartingNewPlayer_Implementation( //
	APlayerController* NewPlayer
) -> void {
	// NOTE: UEcsactEntityPlayerSpawner is responsible for spawning the pawn
	// Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}
