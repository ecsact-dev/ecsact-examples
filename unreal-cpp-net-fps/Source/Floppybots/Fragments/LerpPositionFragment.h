#pragma once

#include "LerpPositionFragment.generated.h"

USTRUCT()

struct FLOPPYBOTS_API FLerpPositionFragment : public FMassFragment {
	GENERATED_BODY() // nolint

	UPROPERTY()
	FVector DesiredPosition;

	FLerpPositionFragment() = default;
};
