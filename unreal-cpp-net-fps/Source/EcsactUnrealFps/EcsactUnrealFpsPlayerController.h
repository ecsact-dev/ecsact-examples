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

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// TODO: set this per-player
	/**
	 * This player ID gets passed to Ecsact when executing actions by this player
	 * controller
	 */
	int32 PlayerId = 0;
};
