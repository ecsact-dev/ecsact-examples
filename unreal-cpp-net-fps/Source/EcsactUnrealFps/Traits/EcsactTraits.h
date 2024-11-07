#pragma once

#include "MassEntityTraitBase.h"
#include "MassMovementFragments.h"
#include "../Fragments/EcsactFragments.h"
#include "EcsactTraits.generated.h"

UCLASS(meta = (DisplayName = "Streaming"))

class ECSACTUNREALFPS_API UEcsactStreamingTrait : public UMassEntityTraitBase {
	GENERATED_BODY() // nolint

protected:
	virtual void BuildTemplate(
		FMassEntityTemplateBuildContext& BuildContext,
		const UWorld&                    World
	) const override;

	UPROPERTY(Category = "Streaming", EditAnywhere)
	FEcsactStreamingFragment Streaming;

	// Add listener to change streaming value
};
