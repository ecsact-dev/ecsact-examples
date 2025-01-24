#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include "generated/EcsactUnrealFps.ecsact.hh"
#include "generated/EcsactUnrealFps.ecsact.systems.hh"

static bool is_overlapping(
	float                         radius,
	const example::fps::Position& pos,
	const example::fps::Position& other_pos
) {
	float x_dist = std::abs(pos.x - other_pos.x);
	float y_dist = std::abs(pos.y - other_pos.y);
	float z_dist = std::abs(pos.z - other_pos.z);

	if(x_dist < radius && y_dist < radius && z_dist < radius) {
		return true;
	} else {
		return false;
	}
}

template<std::floating_point T>
static auto normalize2(T& a, T& b) -> void {
	T magnitude = std::sqrt(a * a + b * b);

	if(std::abs(magnitude) < std::numeric_limits<T>::epsilon()) {
		a = {};
		b = {};
		return;
	}

	a = a / magnitude;
	b = b / magnitude;
}

auto example::fps::PusherExpireChecker::impl(context& ctx) -> void {
	auto pusher = ctx.get<Pusher>();
	pusher.cooldown_remaining -= 0.1f;
	if(pusher.cooldown_remaining < 0.f) {
		ctx.add<PusherExpired>();
	}

	ctx.update(pusher);
}

auto example::fps::PusherApplyExpired::impl(context& ctx) -> void {
	// trivial
}

auto example::fps::StartPush::impl(context& ctx) -> void {
	auto player_id = ctx.get<Player>().player_id;
	if(player_id == ctx.action().player_id) {
		ctx.add(PushCharge{.radius = 3.f});
	}
}

auto example::fps::FinishPush::impl(context& ctx) -> void {
	auto player_id = ctx.get<Player>().player_id;

	if(player_id == ctx.action().player_id) {
		ctx.add(Pusher{1.f});
	}
}

static auto push_radius_to_force(float radius) -> float {
	// TODO
	return 30.f;
}

static auto push_radius_to_tick_count(float radius) -> int16_t {
	// TODO
	return 15;
}

auto example::fps::FinishPush::PushEntities::impl(context& ctx) -> void {
	auto push = ctx._ctx.parent().action<FinishPush>();
	auto player_id = ctx._ctx.parent().get<Player>().player_id;
	if(player_id != push.player_id) {
		return;
	}

	const auto pusher_pos = ctx._ctx.parent().get<Position>();
	const auto push_multipliers = ctx._ctx.parent().get<PushCharge>();

	const auto position = ctx.get<Position>();
	const auto charge = ctx._ctx.parent().get<PushCharge>();
	auto       toggle = ctx.get<Toggle>();

	if(is_overlapping(charge.radius, position, pusher_pos)) {
		auto enemy = ctx.get<Enemy>();
		enemy.player_id = player_id;
		ctx.update(enemy);

		auto force = push_radius_to_force(charge.radius);
		auto tick_count = push_radius_to_tick_count(charge.radius);

		auto push_dir_x = position.x - pusher_pos.x;
		auto push_dir_y = position.y - pusher_pos.y;
		auto push_dir_z = 0.f; // TODO: add a little Z to spice it up

		normalize2(push_dir_x, push_dir_y);

		ctx.add(Pushing{
			.tick_count = tick_count,
			.force_x = push_dir_x * force,
			.force_y = push_dir_y * force,
			.force_z = push_dir_z * force,
		});

		toggle.streaming = false;
		ctx.update(toggle);
	}
}

auto example::fps::RemovePushCharge::impl(context& ctx) -> void {
	// trivial
}

auto example::fps::TickPushCharge::impl(context& ctx) -> void {
	auto push_charge = ctx.get<PushCharge>();
	push_charge.radius += 3.f;
	ctx.update(push_charge);
}

auto example::fps::Move::impl(context& ctx) -> void {
	auto player_id = ctx.get<Player>().player_id;
	auto action = ctx.action();
	if(player_id == action.player_id) {
		ctx.update(MoveDirection{action.x, action.y});
	}
}

auto example::fps::ApplyPush::impl(context& ctx) -> void {
	auto pushing = ctx.get<Pushing>();
	auto velocity = ctx.get<Velocity>();

	if(pushing.tick_count > 0) {
		velocity.x = pushing.force_x;
		velocity.y = pushing.force_y;
		velocity.z = pushing.force_z;

		pushing.tick_count -= 1;
		ctx.update(velocity);
		ctx.update(pushing);
	}
}

auto example::fps::ApplyVelocity::impl(context& ctx) -> void {
	const auto velocity = ctx.get<Velocity>();
	auto       position = ctx.get<Position>();

	// auto x = std::to_string(position.x);
	// auto y = std::to_string(position.y);
	// auto z = std::to_string(position.z);
	//
	// std::string position_str = ("Position: " + x + ", " + y + ", " + z + "\n");
	//
	// auto vel_x = std::to_string(velocity.x);
	// auto vel_y = std::to_string(velocity.y);
	// auto vel_z = std::to_string(velocity.z);
	//
	// std::string velocity_str =
	// 	("Velocity: " + vel_x + ", " + vel_y + ", " + vel_z + "\n");
	// std::puts(velocity_str.c_str());

	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	ctx.update(position);
}

auto example::fps::ApplyDrag::impl(context& ctx) -> void {
	const auto pushing = ctx.get<Pushing>();
	auto       velocity = ctx.get<Velocity>();

	velocity.x = velocity.x * 0.9f;
	velocity.y = velocity.y * 0.9f;
	velocity.z = velocity.z * 0.9f;

	if(std::abs(velocity.x) <= 2 && pushing.tick_count <= 0) {
		ctx.add<RemovePushingTag>();
		ctx.add(Stunned{10.f});
	}
	ctx.update(velocity);
}

auto example::fps::ResumeStreaming::impl(context& ctx) -> void {
	ctx.update(Toggle{.streaming = true});
}

auto example::fps::TogglePushedEntities::impl(context& ctx) -> void {
	const auto toggle = ctx.get<Toggle>();

	ctx.stream_toggle<Position>(toggle.streaming);
	ctx.stream_toggle<Rotation>(toggle.streaming);
}

auto example::fps::RemovePushing::impl(context& ctx) -> void {
}

auto example::fps::StunTimer::impl(context& ctx) -> void {
	auto stunned = ctx.get<Stunned>();
	stunned.remaining -= 0.1f;
	if(stunned.remaining <= 0.f) {
		ctx.add<StunnedExpired>();
	}

	ctx.update(stunned);
}

auto example::fps::StunnedExpiry::impl(context& ctx) -> void {
	// trivial
}
