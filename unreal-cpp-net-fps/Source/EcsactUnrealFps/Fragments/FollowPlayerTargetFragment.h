#pragma once

#include "MassEntityTypes.h"
#include "FollowPlayerTargetFragment.generated.h"

USTRUCT()

struct FLOPPYBOTS_API FFollowPlayerTargetFragment : public FMassSharedFragment {
	GENERATED_BODY()

	auto SetPlayerPosition(int32 Entity, FVector Position) -> void;
	auto GetPlayerPosition(int32 Entity) const -> FVector;

	auto GetClosestPlayerPosition(FVector Source) const -> FVector;

private:
	UPROPERTY()
	TArray<int32> PlayerEntities;

	UPROPERTY()
	TArray<FVector> PlayerPositions;
};
