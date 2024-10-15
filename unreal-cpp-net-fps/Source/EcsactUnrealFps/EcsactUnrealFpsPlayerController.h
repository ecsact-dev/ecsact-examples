// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EcsactUnrealFpsPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()

class ECSACTUNREALFPS_API AEcsactUnrealFpsPlayerController
	: public APlayerController {
	GENERATED_BODY()

protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	virtual void BeginPlay() override;

public:
	// TODO: set this per-player
	/**
	 * This player ID gets passed to Ecsact when executing actions by this player controller
	 */
	int32 PlayerId = 0;
};
