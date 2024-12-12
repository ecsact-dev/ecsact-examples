#pragma once

#include "MassEntityTraitBase.h"
#include "EcsactUnrealFps/Fragments/LerpPositionParameters.h"
#include "LerpPositionTrait.generated.h"

UCLASS(meta = (DisplayName = "Avoidance"))
class ECSACTUNREALFPS_API ULerpPositionTrait : public UMassEntityTraitBase {
	GENERATED_BODY()

protected:
	
	auto BuildTemplate( //
		FMassEntityTemplateBuildContext& BuildContext,
		const UWorld& World
	) const -> void override;

	UPROPERTY(EditAnywhere, Category="")
	FLerpPositionParameters PositionParameters;
};