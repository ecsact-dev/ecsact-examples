#pragma once

#include "MassEntityTypes.h"
#include "LerpPositionParameters.generated.h"

USTRUCT()

struct FLOPPYBOTS_API FLerpPositionParameters
	: public FMassConstSharedFragment {
	GENERATED_BODY()

	/** Instead of lerping - instantly set position */
	UPROPERTY(EditAnywhere, Category = "General")
	bool Disabled = false;

	/** How fast position should be interpolated */
	UPROPERTY(
		EditAnywhere,
		Category = "General",
		meta = (ClampMin = "0.0", ForceUnits = "cm")
	)
	float Speed = 400.f;
};
