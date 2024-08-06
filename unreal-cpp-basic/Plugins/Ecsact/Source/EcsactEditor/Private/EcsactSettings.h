#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EcsactSettings.generated.h"

UCLASS(Config = Ecsact, DefaultConfig)

class UEcsactSettings : public UObject {
	GENERATED_BODY()

public:
	UEcsactSettings();

	UPROPERTY(EditAnywhere, Config, Category = Ecsact)
	TArray<FString> Recipes;
};
