#pragma once

#include "MassEntityTraitBase.h"
#include "EcsactUnrealFps/Fragments/LerpPositionParameters.h"
#include "FollowPlayerTrait.generated.h"

UCLASS(meta = (DisplayName = "Follow Player"))

class ECSACTUNREALFPS_API UFollowPlayerTrait : public UMassEntityTraitBase {
	GENERATED_BODY()

protected:
	auto BuildTemplate( //
		FMassEntityTemplateBuildContext& BuildContext,
		const UWorld&                    World
	) const -> void override;
};
