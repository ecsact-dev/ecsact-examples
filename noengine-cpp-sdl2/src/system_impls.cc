#include "generated/example.ecsact.systems.hh"

#include <algorithm>
#include <iostream>
#include <format>
#include "simulation_config.hh"

constexpr auto player_speed = 600.f;
constexpr auto player_jump_power = 1800.f;
constexpr auto horizontal_drag = 5000.0f;
constexpr auto projectile_speed = 2500.0f;
constexpr auto terminal_velocity = 5000.0f;

auto example::Move::impl(context& ctx) -> void {
	auto move_dir_x = std::clamp(ctx.action().dir_x, -1.f, 1.f);
	auto move_dir_y = std::clamp(ctx.action().dir_y, -1.f, 1.f);
	ctx.update(Moving{move_dir_x, move_dir_y});
}

auto example::Fire::impl(context& ctx) -> void {
	auto player_pos = ctx.get<Position>();
	auto moving = ctx.get<Moving>();

	for(auto i = 0; 50 > i; ++i) {
		auto projectile_pos = Position{player_pos};
		projectile_pos.x += moving.dir_x * 10.f;
		projectile_pos.y += moving.dir_y * 10.f;
		projectile_pos.x += i;
		projectile_pos.y += i;

		auto projectile_vel = Velocity{};
		projectile_vel.x = moving.dir_x * projectile_speed;
		projectile_vel.y = moving.dir_y * projectile_speed;
		projectile_vel.x += i;
		projectile_vel.y += i;
		ctx._ctx.generate(
			Projectile{},
			std::move(projectile_pos),
			std::move(projectile_vel)
		);
	}
}

auto example::ReverseGravity::impl(context& ctx) -> void {
	auto gravity = ctx.get<Gravity>();
	gravity.value = -gravity.value;
	ctx.update(gravity);
}

auto example::Jump::impl(context& ctx) -> void {
	auto vel = ctx.get<Velocity>();
	vel.y = player_jump_power;
	ctx.update(vel);
}

auto example::Movement::impl(context& ctx) -> void {
	auto moving = ctx.get<Moving>();
	if(moving.dir_x != 0.f) {
		auto vel = ctx.get<Velocity>();
		vel.x = moving.dir_x * player_speed;
		ctx.update(vel);
	}
}

auto example::PhysicsParent::impl(context&) -> void {
}

auto example::PhysicsParent::Physics::impl(context& ctx) -> void {
	auto gravity = ctx._ctx.parent().get<Gravity>().value;
	auto vel = ctx.get<Velocity>();
	vel.y -= gravity * simulation_config::fixed_delta_time;

	if(vel.x > 0.f) {
		vel.x = std::max(
			0.f,
			vel.x - (horizontal_drag * simulation_config::fixed_delta_time)
		);
	} else if(vel.x < 0.f) {
		vel.x = std::min(
			0.f,
			vel.x + (horizontal_drag * simulation_config::fixed_delta_time)
		);
	}

	vel.y = std::clamp(vel.y, -terminal_velocity, terminal_velocity);
	vel.y = std::clamp(vel.y, -terminal_velocity, terminal_velocity);

	ctx.update(vel);
}

auto example::ApplyVelocity::impl(context& ctx) -> void {
	auto vel = ctx.get<Velocity>();
	auto pos = ctx.get<Position>();
	pos.x += vel.x * simulation_config::fixed_delta_time;
	pos.y += vel.y * simulation_config::fixed_delta_time;
	ctx.update(pos);
}
