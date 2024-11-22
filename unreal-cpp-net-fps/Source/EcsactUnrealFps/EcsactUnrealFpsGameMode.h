// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EcsactUnrealFpsGameMode.generated.h"

UCLASS(minimalapi)

class AEcsactUnrealFpsGameMode : public AGameModeBase {
	GENERATED_BODY()

protected:
	void HandleStartingNewPlayer_Implementation( //
		APlayerController* NewPlayer
	) override;

	// auto ChoosePlayerStart_Implementation( //
	// 	AController* Player
	// ) -> AActor* override;

	// auto SpawnDefaultPawnFor_Implementation(
	// 	AController* NewPlayer,
	// 	AActor*      StartSpot
	// ) -> AActor* override;

public:
	AEcsactUnrealFpsGameMode();

	auto ShouldSpawnAtStartSpot(AController* Controller) -> bool override;
};
