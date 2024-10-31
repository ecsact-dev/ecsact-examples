#pragma once

#include "MassEntityTypes.h"
#include "Math/Vector.h"
#include "Ecsact/runtime/common.h"

#include "EcsactFragments.generated.h"

USTRUCT()

struct ECSACTUNREALFPS_API FEcsactEntityFragment : public FMassFragment {
	GENERATED_BODY() // nolint

	FEcsactEntityFragment() = default;

	FEcsactEntityFragment(const ecsact_entity_id EntityId) : Id(EntityId) {
	}

	void SetId(const ecsact_entity_id EntityId) {
		Id = EntityId;
	}

	ecsact_entity_id GetId() const {
		return Id;
	}

	ecsact_entity_id& GetMutableId() {
		return Id;
	}

private:
	ecsact_entity_id Id;
};

USTRUCT()

struct ECSACTUNREALFPS_API FEcsactStreamingFragment
	: public FMassSharedFragment {
	GENERATED_BODY() // nolint

	FEcsactStreamingFragment() = default;

	UPROPERTY(EditAnywhere, Category = "Streaming")
	bool ShouldStream;
};

USTRUCT()

struct ECSACTUNREALFPS_API FEcsactPositionFragment : public FMassFragment {
	GENERATED_BODY() // nolint

	FEcsactPositionFragment() = default;

	FEcsactPositionFragment(const FVector StartPosition)
		: Position(StartPosition) {
	}

	FVector GetPosition() const {
		return Position;
	}

	FVector& GetMutablePosition() {
		return Position;
	}

	void SetPosition(const FVector& NewPosition) {
		Position = NewPosition;
	}

private:
	FVector Position;
};
