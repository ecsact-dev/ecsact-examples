
#include "generated/example.ecsact.systems.hh"

#include <iostream>
#include <format>
#include <algorithm>
#include <SDL.h>
#include <SDL_render.h>

extern int viewport_width;
extern int viewport_height;

auto example::ViewportCollision::impl(context& ctx) -> void {
	auto viewport_width_f = static_cast<float>(viewport_width);
	auto viewport_height_f = static_cast<float>(viewport_height);
	auto pos = ctx.get<Position>();

	pos.x = std::clamp( //
		pos.x,
		-(viewport_width_f / 2.f),
		viewport_width_f / 2.f
	);
	pos.y = std::clamp( //
		pos.y,
		-(viewport_height_f / 2.f),
		viewport_height_f / 2.f
	);

	ctx.update(pos);
}
