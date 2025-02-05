// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FloppybotsGameMode.generated.h"

UCLASS(minimalapi)

class AFloppybotsGameMode : public AGameModeBase {
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
	AFloppybotsGameMode();

	auto ShouldSpawnAtStartSpot(AController* Controller) -> bool override;
};
