#pragma once

#include "Floppybots/Fragments/LerpPositionParameters.h"
#include "FollowPlayerTrait.generated.h"
#include "MassEntityTraitBase.h"

UCLASS(meta = (DisplayName = "Follow Player"))

class FLOPPYBOTS_API UFollowPlayerTrait : public UMassEntityTraitBase {
	GENERATED_BODY()

protected:
	auto BuildTemplate(
		FMassEntityTemplateBuildContext& BuildContext,
		const UWorld& World
	) const -> void override;
};
