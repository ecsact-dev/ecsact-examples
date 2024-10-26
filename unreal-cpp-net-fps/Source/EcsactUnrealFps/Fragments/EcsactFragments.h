#pragma once

#include "MassEntityTypes.h"
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
