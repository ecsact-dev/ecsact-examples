#pragma once

#include "CoreMinimal.h"
#include "Floppybots/Floppybots__ecsact__ue.h"
#include "GameFramework/Actor.h"
#include "Math/Color.h"
#include "Floppybot.generated.h"

UCLASS(Blueprintable)

class FLOPPYBOTS_API AFloppybot : public AActor {
	GENERATED_BODY()

public:
	AFloppybot();

	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitStunned(FFloppybotsStunned Stunned);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateStunned(FFloppybotsStunned Stunned);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoveStunned(FFloppybotsStunned Stunned);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitEnemy(FFloppybotsEnemy Enemy);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateEnemy(FFloppybotsEnemy Enemy);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoveEnemy(FFloppybotsEnemy Enemy);
};
