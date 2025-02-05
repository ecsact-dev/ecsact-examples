#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FloppybotsPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()

class FLOPPYBOTS_API AFloppybotsPlayerController : public APlayerController {
	GENERATED_BODY()

protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	/**
	 * This player ID gets passed to Ecsact when executing actions by this player
	 * controller
	 */
	int32 PlayerId = 0;
};
