#pragma once

#include "MassEntityTypes.h"
#include "LerpPositionParameters.generated.h"

USTRUCT()

struct ECSACTUNREALFPS_API FLerpPositionParameters
	: public FMassSharedFragment {
	GENERATED_BODY()

	/** How fast position should be interpolated */
	UPROPERTY(
		EditAnywhere,
		Category = "General",
		meta = (ClampMin = "0.0", ForceUnits = "cm")
	)
	float Speed = 400.f;
};
