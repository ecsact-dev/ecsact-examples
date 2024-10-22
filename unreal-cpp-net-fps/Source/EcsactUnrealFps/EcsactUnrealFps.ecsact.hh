// GENERATED FILE - DO NOT EDIT
#pragma once

#include <cstdint>
#include <compare>
#include "ecsact/runtime/common.h"

namespace example::fps {

struct Projectile {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(1);
	auto operator<=>(const example::fps::Projectile&) const = default;
};
struct Player {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(2);
	int32_t player_id;
	auto operator<=>(const example::fps::Player&) const = default;
};
struct Rotation {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(3);
	float pitch;
	float yaw;
	float roll;
	auto operator<=>(const example::fps::Rotation&) const = default;
};
struct Position {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(4);
	float x;
	float y;
	float z;
	auto operator<=>(const example::fps::Position&) const = default;
};
struct Fire {
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_action_id>(5);
	struct context;
	static void impl(context&);
	int32_t player_id;
	auto operator<=>(const example::fps::Fire&) const = default;
};

}// namespace example::fps
