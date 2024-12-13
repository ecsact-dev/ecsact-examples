#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <string>
#include "generated/EcsactUnrealFps.ecsact.hh"
#include "generated/EcsactUnrealFps.ecsact.systems.hh"

bool is_overlapping(
	int16_t                      radius,
	const example::fps::Position pos,
	const example::fps::Position other_pos
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

auto example::fps::Push::impl(context& ctx) -> void {
	auto player_id = ctx.get<Player>().player_id;
	if(player_id == ctx.action().player_id) {
		ctx.add(Pusher{1.f});
	}
}

auto example::fps::Move::impl(context& ctx) -> void {
	auto player_id = ctx.get<Player>().player_id;
	auto action = ctx.action();
	if(player_id == action.player_id) {
		ctx.update(MoveDirection{action.x, action.y});
	}
}

auto example::fps::Push::PushEntities::impl(context& ctx) -> void {
	auto push = ctx._ctx.parent().action<Push>();
	auto player_id = ctx._ctx.parent().get<Player>().player_id;
	if(player_id != push.player_id) {
		return;
	}

	const auto pusher_pos = ctx._ctx.parent().get<Position>();
	const auto position = ctx.get<Position>();
	auto       toggle = ctx.get<Toggle>();

	if(is_overlapping(push.radius, position, pusher_pos)) {
		auto push_dir_x = std::clamp(position.x - pusher_pos.x, -1.f, 1.f);
		auto push_dir_y = std::clamp(position.y - pusher_pos.y, -1.f, 1.f);
		auto push_dir_z = 0.f; // TODO: add a little Z to spice it up

		ctx.add(Pushing{
			.tick_count = push.tick_count,
			.force_x = push_dir_x * push.force,
			.force_y = push_dir_y * push.force,
			.force_z = push_dir_z * push.force,
		});

		toggle.streaming = false;
		ctx.update(toggle);
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
	auto       toggle = ctx.get<Toggle>();

	velocity.x = velocity.x * 0.9f;
	velocity.y = velocity.y * 0.9f;
	velocity.z = velocity.z * 0.9f;

	if(std::abs(velocity.x) <= 2 && pushing.tick_count <= 0) {
		toggle.streaming = true;
		ctx.add<RemovePushingTag>();
		ctx.update(toggle);
	}
	ctx.update(velocity);
}

auto example::fps::TogglePushedEntities::impl(context& ctx) -> void {
	const auto toggle = ctx.get<Toggle>();

	ctx.stream_toggle<Position>(toggle.streaming);
}

auto example::fps::RemovePushing::impl(context& ctx) -> void {
}
