#include "generated/example.ecsact.systems.hh"

#include <iostream>
#include <format>
#include <SDL.h>
#include <SDL_render.h>

extern SDL_Renderer* renderer;
extern int           viewport_width;
extern int           viewport_height;

static auto viewport_relative_pos(const auto& pos, auto& out_pos) -> void {
	auto viewport_width_f = static_cast<float>(viewport_width);
	auto viewport_height_f = static_cast<float>(viewport_height);
	out_pos.x = pos.x;
	out_pos.y = -pos.y;
	out_pos.x += viewport_width_f / 2.f;
	out_pos.y += viewport_height_f / 2.f;
	out_pos.y -= out_pos.h / 2.f;
	out_pos.x -= out_pos.w / 2.f;
}

auto example::Render::impl(context& ctx) -> void {
	auto pos = ctx.get<Position>();
	auto rect = SDL_Rect{};
	rect.w = 10.0f;
	rect.h = 10.0f;
	viewport_relative_pos(pos, rect);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

auto example::RenderAimer::impl(context& ctx) -> void {
	constexpr auto aimer_size = 5.f;
	SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);

	auto pos = ctx.get<Position>();
	auto moving = ctx.get<Moving>();
	auto aimer_rect = SDL_Rect{};
	aimer_rect.w = aimer_size;
	aimer_rect.h = aimer_size;
	viewport_relative_pos(pos, aimer_rect);

	auto start_point_x = aimer_rect.x;
	auto start_point_y = aimer_rect.y;
	aimer_rect.x += moving.dir_x * 100.f;
	aimer_rect.y -= moving.dir_y * 100.f;
	auto end_point_x = aimer_rect.x;
	auto end_point_y = aimer_rect.y;

	SDL_RenderDrawLine(
		renderer,
		start_point_x,
		start_point_y,
		end_point_x,
		end_point_y
	);
	SDL_RenderFillRect(renderer, &aimer_rect);
}
