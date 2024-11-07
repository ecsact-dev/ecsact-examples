// GENERATED FILE - DO NOT EDIT
#pragma once

#include <cstdint>
#include <compare>
#include "ecsact/runtime/common.h"

namespace example::fps {

struct Player {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(1);
	int32_t player_id;
	auto operator<=>(const example::fps::Player&) const = default;
};
struct Rotation {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(2);
	float pitch;
	float yaw;
	float roll;
	auto operator<=>(const example::fps::Rotation&) const = default;
};
struct Position {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(3);
	float x;
	float y;
	float z;
	auto operator<=>(const example::fps::Position&) const = default;
};
struct MassEntity {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(4);
	auto operator<=>(const example::fps::MassEntity&) const = default;
};
struct Velocity {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(5);
	float x;
	float y;
	float z;
	auto operator<=>(const example::fps::Velocity&) const = default;
};
struct Pushing {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(6);
	int16_t tick_count;
	int16_t force_x;
	int16_t force_y;
	int16_t force_z;
	auto operator<=>(const example::fps::Pushing&) const = default;
};
struct Toggle {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(7);
	int8_t streaming;
	auto operator<=>(const example::fps::Toggle&) const = default;
};
struct RemovePushingTag {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(11);
	auto operator<=>(const example::fps::RemovePushingTag&) const = default;
};
struct Push {
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_action_id>(9);
	struct PushEntities {
		static constexpr auto id = static_cast<ecsact_system_id>(10);
		struct context;
		static void impl(context&);
	};
	struct context;
	static void impl(context&);
	int32_t player_id;
	int16_t radius;
	int16_t tick_count;
	int16_t force_x;
	int16_t force_y;
	int16_t force_z;
	auto operator<=>(const example::fps::Push&) const = default;
};
struct RemoveToggle {
	static constexpr auto id = static_cast<ecsact_system_id>(8);
	struct context;
	static void impl(context&);
};
struct ApplyPush {
	static constexpr auto id = static_cast<ecsact_system_id>(12);
	struct context;
	static void impl(context&);
};
struct ApplyVelocity {
	static constexpr auto id = static_cast<ecsact_system_id>(13);
	struct context;
	static void impl(context&);
};
struct ApplyDrag {
	static constexpr auto id = static_cast<ecsact_system_id>(14);
	struct context;
	static void impl(context&);
};
struct TogglePushedEntities {
	static constexpr auto id = static_cast<ecsact_system_id>(15);
	struct context;
	static void impl(context&);
};
struct RemovePushing {
	static constexpr auto id = static_cast<ecsact_system_id>(16);
	struct context;
	static void impl(context&);
};

}// namespace example::fps
