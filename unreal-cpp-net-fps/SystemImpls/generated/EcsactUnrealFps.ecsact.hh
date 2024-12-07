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
struct Pusher {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(2);
	float cooldown_remaining;
	auto operator<=>(const example::fps::Pusher&) const = default;
};
struct PusherExpired {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(3);
	auto operator<=>(const example::fps::PusherExpired&) const = default;
};
struct Rotation {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(4);
	float pitch;
	float yaw;
	float roll;
	auto operator<=>(const example::fps::Rotation&) const = default;
};
struct Position {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(5);
	float x;
	float y;
	float z;
	auto operator<=>(const example::fps::Position&) const = default;
};
struct MassEntity {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(6);
	auto operator<=>(const example::fps::MassEntity&) const = default;
};
struct Velocity {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(7);
	float x;
	float y;
	float z;
	auto operator<=>(const example::fps::Velocity&) const = default;
};
struct Pushing {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(8);
	int16_t tick_count;
	float force_x;
	float force_y;
	float force_z;
	auto operator<=>(const example::fps::Pushing&) const = default;
};
struct Toggle {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(9);
	int8_t streaming;
	auto operator<=>(const example::fps::Toggle&) const = default;
};
struct MoveDirection {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(14);
	float x;
	float y;
	auto operator<=>(const example::fps::MoveDirection&) const = default;
};
struct RemovePushingTag {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(16);
	auto operator<=>(const example::fps::RemovePushingTag&) const = default;
};
struct Push {
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_action_id>(12);
	struct PushEntities {
		static constexpr auto id = static_cast<ecsact_system_id>(13);
		struct context;
		static void impl(context&);
	};
	struct context;
	static void impl(context&);
	int32_t player_id;
	int16_t radius;
	int16_t tick_count;
	float force;
	auto operator<=>(const example::fps::Push&) const = default;
};
struct Move {
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_action_id>(15);
	struct context;
	static void impl(context&);
	int32_t player_id;
	float x;
	float y;
	auto operator<=>(const example::fps::Move&) const = default;
};
struct PusherExpireChecker {
	static constexpr auto id = static_cast<ecsact_system_id>(10);
	struct context;
	static void impl(context&);
};
struct PusherApplyExpired {
	static constexpr auto id = static_cast<ecsact_system_id>(11);
	struct context;
	static void impl(context&);
};
struct ApplyPush {
	static constexpr auto id = static_cast<ecsact_system_id>(17);
	struct context;
	static void impl(context&);
};
struct ApplyVelocity {
	static constexpr auto id = static_cast<ecsact_system_id>(18);
	struct context;
	static void impl(context&);
};
struct ApplyDrag {
	static constexpr auto id = static_cast<ecsact_system_id>(19);
	struct context;
	static void impl(context&);
};
struct TogglePushedEntities {
	static constexpr auto id = static_cast<ecsact_system_id>(20);
	struct context;
	static void impl(context&);
};
struct RemovePushing {
	static constexpr auto id = static_cast<ecsact_system_id>(21);
	struct context;
	static void impl(context&);
};

}// namespace example::fps
