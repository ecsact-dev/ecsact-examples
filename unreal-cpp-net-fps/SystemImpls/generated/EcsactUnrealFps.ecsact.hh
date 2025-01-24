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
struct Stunned {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(6);
	float remaining;
	auto operator<=>(const example::fps::Stunned&) const = default;
};
struct StunnedExpired {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(7);
	auto operator<=>(const example::fps::StunnedExpired&) const = default;
};
struct PushCharge {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(8);
	float radius;
	auto operator<=>(const example::fps::PushCharge&) const = default;
};
struct Enemy {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(9);
	int32_t player_id;
	auto operator<=>(const example::fps::Enemy&) const = default;
};
struct Velocity {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(10);
	float x;
	float y;
	float z;
	auto operator<=>(const example::fps::Velocity&) const = default;
};
struct Pushing {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(11);
	int16_t tick_count;
	float force_x;
	float force_y;
	float force_z;
	auto operator<=>(const example::fps::Pushing&) const = default;
};
struct Toggle {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(12);
	int8_t streaming;
	auto operator<=>(const example::fps::Toggle&) const = default;
};
struct MoveDirection {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(21);
	float x;
	float y;
	auto operator<=>(const example::fps::MoveDirection&) const = default;
};
struct RemovePushingTag {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(23);
	auto operator<=>(const example::fps::RemovePushingTag&) const = default;
};
struct StartPush {
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_action_id>(16);
	struct context;
	static void impl(context&);
	int32_t player_id;
	auto operator<=>(const example::fps::StartPush&) const = default;
};
struct FinishPush {
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_action_id>(17);
	struct PushEntities {
		static constexpr auto id = static_cast<ecsact_system_id>(18);
		struct context;
		static void impl(context&);
	};
	struct context;
	static void impl(context&);
	int32_t player_id;
	auto operator<=>(const example::fps::FinishPush&) const = default;
};
struct Move {
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_action_id>(22);
	struct context;
	static void impl(context&);
	int32_t player_id;
	float x;
	float y;
	auto operator<=>(const example::fps::Move&) const = default;
};
struct StunTimer {
	static constexpr auto id = static_cast<ecsact_system_id>(13);
	struct context;
	static void impl(context&);
};
struct PusherExpireChecker {
	static constexpr auto id = static_cast<ecsact_system_id>(14);
	struct context;
	static void impl(context&);
};
struct PusherApplyExpired {
	static constexpr auto id = static_cast<ecsact_system_id>(15);
	struct context;
	static void impl(context&);
};
struct RemovePushCharge {
	static constexpr auto id = static_cast<ecsact_system_id>(19);
	struct context;
	static void impl(context&);
};
struct TickPushCharge {
	static constexpr auto id = static_cast<ecsact_system_id>(20);
	struct context;
	static void impl(context&);
};
struct ApplyPush {
	static constexpr auto id = static_cast<ecsact_system_id>(24);
	struct context;
	static void impl(context&);
};
struct ApplyVelocity {
	static constexpr auto id = static_cast<ecsact_system_id>(25);
	struct context;
	static void impl(context&);
};
struct ApplyDrag {
	static constexpr auto id = static_cast<ecsact_system_id>(26);
	struct context;
	static void impl(context&);
};
struct ResumeStreaming {
	static constexpr auto id = static_cast<ecsact_system_id>(27);
	struct context;
	static void impl(context&);
};
struct TogglePushedEntities {
	static constexpr auto id = static_cast<ecsact_system_id>(28);
	struct context;
	static void impl(context&);
};
struct RemovePushing {
	static constexpr auto id = static_cast<ecsact_system_id>(29);
	struct context;
	static void impl(context&);
};
struct StunnedExpiry {
	static constexpr auto id = static_cast<ecsact_system_id>(30);
	struct context;
	static void impl(context&);
};

}// namespace example::fps
