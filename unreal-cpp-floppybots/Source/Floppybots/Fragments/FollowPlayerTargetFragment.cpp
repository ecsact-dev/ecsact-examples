#include "FollowPlayerTargetFragment.h"

auto FFollowPlayerTargetFragment::SetPlayerPosition(
	int32 Entity,
	FVector Position
) -> void {
	auto i = PlayerEntities.IndexOfByKey(Entity);
	if(i == INDEX_NONE) {
		PlayerEntities.Add(Entity);
		PlayerPositions.Add(Position);
	} else {
		PlayerPositions[i] = Position;
	}
}

auto FFollowPlayerTargetFragment::GetPlayerPosition(int32 Entity
) const -> FVector {
	auto i = PlayerEntities.IndexOfByKey(Entity);
	if(i == INDEX_NONE) {
		UE_LOG(LogTemp, Error, TEXT("Attempted to get non player position"));
		return FVector{};
	}

	return PlayerPositions[i];
}

auto FFollowPlayerTargetFragment::GetClosestPlayerPosition( //
	FVector Source
) const -> FVector {
	if(PlayerPositions.IsEmpty()) {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("GetClosestPlayerPosition() called with no player positions!")
		);
		return Source;
	}

	auto closest_index = 0;
	auto closest_dist = FVector::Dist(Source, PlayerPositions[0]);
	for(auto i = 1; PlayerPositions.Num() > i; ++i) {
		auto player_dist = FVector::Dist(Source, PlayerPositions[i]);
		if(FVector::Dist(Source, PlayerPositions[i]) < closest_dist) {
			closest_index = i;
			closest_dist = player_dist;
		}
	}

	return PlayerPositions[closest_index];
}
