#pragma once

#include "MassEntityTypes.h"
#include "Ecsact/runtime/common.h"

#include "EcsactFragments.generated.h"

/**
 * Tag indiciating that this mass entity should be streamed.
 */
USTRUCT()

struct ECSACTUNREALFPS_API FEcsactStreamTag : public FMassTag {
	GENERATED_BODY()
};
