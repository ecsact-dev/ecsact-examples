#pragma once

#include "CoreMinimal.h"
#include "EcsactUnreal/EcsactRunnerSubsystem.h"
#include "SystemImpls.generated.h"

UCLASS()

class ECSACTUNREALCPPBASIC_API USystemImpls : public UEcsactRunnerSubsystem {
	GENERATED_BODY()
public:
	auto RunnerStart_Implementation(UEcsactRunner* Runner) -> void override;
};
