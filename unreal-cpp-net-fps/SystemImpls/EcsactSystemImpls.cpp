#include <utility>
#include <cstdio>
#include "generated/EcsactUnrealFps.ecsact.hh"
#include "generated/EcsactUnrealFps.ecsact.systems.hh"

auto example::fps::StartFiring::impl(context& ctx) -> void {
	ctx.add(Firing{});
	ctx.stream_toggle<Position>(false);
	ctx.stream_toggle<Rotation>(false);
}

auto example::fps::StopFiring::impl(context& ctx) -> void {
	ctx.remove<Firing>();
	ctx.stream_toggle<Position>(true);
	ctx.stream_toggle<Rotation>(true);
}

auto example::fps::Fire::impl(context& ctx) -> void {
	auto player_pos = ctx.get<Position>();
	auto player_rot = ctx.get<Rotation>();
	std::puts("generating projectile entity");
	ctx._ctx.generate( //
		Projectile{},
		std::move(player_pos),
		std::move(player_rot)
	);
}
