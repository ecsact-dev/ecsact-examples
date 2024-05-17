#include "generated/example.ecsact.systems.hh"

#include <iostream>
#include <format>
#include <algorithm>
#include "cute_c2.h"
#include "simulation_config.hh"

constexpr auto push_pressure_strength = 1000.f;

auto example::AlwaysRemoveColliding::impl(context& ctx) -> void {
}

auto example::CollisionPressurePush::impl(context& ctx) -> void {
	auto vel = ctx.get<Velocity>();
	auto colliding = ctx.get<Colliding>();

	vel.x += colliding.pressure_dir_x * push_pressure_strength *
		simulation_config::fixed_delta_time;
	vel.y += colliding.pressure_dir_y * push_pressure_strength *
		simulation_config::fixed_delta_time;

	ctx.update(vel);
}

auto example::CollisionParent::impl(context& ctx) -> void {
}

auto example::CollisionParent::Collision::impl(context& ctx) -> void {
	if(ctx._ctx.same(ctx._ctx.parent())) {
		return;
	}

	auto parent_pos = ctx._ctx.parent().get<Position>();
	auto pos = ctx.get<Position>();

	auto circle = c2Circle{
		.p = {pos.x, pos.y},
		.r = 10.f,
	};

	auto parent_circle = c2Circle{
		.p = {parent_pos.x, parent_pos.y},
		.r = 10.f,
	};

	auto manifold = c2Manifold{};
	c2CircletoCircleManifold(circle, parent_circle, &manifold);
	if(manifold.count > 0) {
		float max_depth = 0.f;
		for(int i = 0; manifold.count > i; ++i) {
			if(manifold.depths[i] > max_depth) {
				max_depth = manifold.depths[i];
			}
		}

		auto push_x = manifold.n.x * max_depth;
		auto push_y = manifold.n.y * max_depth;
		if(push_y < 0.3f && push_y >= 0.f) {
			push_y = 0.3f;
		}

		ctx.add(Colliding{push_x, push_y});
	}
}
