#include <utility>
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps.ecsact.systems.hh"

auto example::fps::Fire::impl(context& ctx) -> void {
	// if(ctx.get<Player>().player_id == ctx.action().player_id) {
	auto player_pos = ctx.get<Position>();
	auto player_rot = ctx.get<Rotation>();
	ctx._ctx.generate( //
		Projectile{},
		std::move(player_pos),
		std::move(player_rot)
	);
	// }
}
