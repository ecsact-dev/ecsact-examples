#include <utility>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
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
	// if(ctx.get<Player>().player_id == ctx.action().player_id) {
	ctx.add(Pusher{1.f});
}

auto example::fps::Push::PushEntities::impl(context& ctx) -> void {
	const auto parent_pos = ctx._ctx.parent().get<Position>();
	const auto tick_count = ctx._ctx.parent().action<Push>().tick_count;
	const auto radius = ctx._ctx.parent().action<Push>().radius;

	const auto force_x = ctx._ctx.parent().action<Push>().force_x;
	const auto force_y = ctx._ctx.parent().action<Push>().force_y;
	const auto force_z = ctx._ctx.parent().action<Push>().force_z;

	const auto position = ctx.get<Position>();

	if(is_overlapping(radius, position, parent_pos)) {
		std::puts("Found overlapping Entity, adding Pushing component!\n");
		ctx.add(Pushing{
			.tick_count = tick_count,
			.force_x = force_x,
			.force_y = force_y,
			.force_z = force_z,
		});
		ctx.add<Toggle>({.streaming = false});
	} else {
		std::puts("Entity too far away to push");
	}
}

auto example::fps::ApplyPush::impl(context& ctx) -> void {
	std::puts("In apply push\n");
	auto pushing = ctx.get<Pushing>();
	auto velocity = ctx.get<Velocity>();

	if(pushing.tick_count > 0) {
		std::puts("Applying force on push");
		velocity.x += pushing.force_x;
		velocity.y += pushing.force_y;
		velocity.z += pushing.force_z;

		pushing.tick_count -= 1;
		ctx.update(pushing);
	}
}

auto example::fps::ApplyVelocity::impl(context& ctx) -> void {
	std::puts("Applying velocity");
	const auto velocity = ctx.get<Velocity>();
	auto       position = ctx.get<Position>();

	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	ctx.update(position);
}

auto example::fps::ApplyDrag::impl(context& ctx) -> void {
	std::puts("Applying drag");
	const auto pushing = ctx.get<Pushing>();
	auto       velocity = ctx.get<Velocity>();

	velocity.x = velocity.x * 0.9f;
	velocity.y = velocity.y * 0.9f;
	velocity.z = velocity.z * 0.9f;

	if(velocity.x <= 2 && pushing.tick_count <= 0) {
		ctx.add<Toggle>({.streaming = true});
		ctx.add<RemovePushingTag>();
	}
}

auto example::fps::TogglePushedEntities::impl(context& ctx) -> void {
	std::puts("Toggling pushed entities");
	const auto toggle = ctx.get<Toggle>();

	ctx.stream_toggle<Position>(toggle.streaming);
}

auto example::fps::RemoveToggle::impl(context& ctx) -> void {
}

auto example::fps::RemovePushing::impl(context& ctx) -> void {
}
