// GENERATED FILE - DO NOT EDIT
#pragma once

#include <cstdint>
#include <compare>
#include "ecsact/runtime/common.h"

namespace example {

struct Position {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(1);
	float x;
	float y;
	float z;
	auto operator<=>(const example::Position&) const = default;
};
struct Velocity {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(2);
	float x;
	float y;
	float z;
	auto operator<=>(const example::Velocity&) const = default;
};
struct Gravity {
	static constexpr auto id = static_cast<ecsact_system_id>(3);
	struct context;
	static void impl(context&);
};
struct FloorBounce {
	static constexpr auto id = static_cast<ecsact_system_id>(4);
	struct context;
	static void impl(context&);
};
struct ApplyVelocity {
	static constexpr auto id = static_cast<ecsact_system_id>(5);
	struct context;
	static void impl(context&);
};

}// namespace example
