#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFpsConnect.generated.h"

UCLASS()

class UEcsactUnrealFpsConnect : public UObject {
	GENERATED_BODY()

	static void CreateInitialEntities();

public:
	UFUNCTION(BlueprintCallable, Category = "Ecsact Runtime")
	static void UnrealFpsConnect(FString ConnectionString);
};
