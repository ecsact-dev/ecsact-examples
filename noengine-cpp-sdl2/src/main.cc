#include <string>
#include <array>
#include <format>
#include <SDL.h>
#include <SDL_main.h>
#include "tracy/Tracy.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "ecsact/runtime/core.hh"
#include "ecsact/runtime/dynamic.h"
#include "generated/example.ecsact.systems.hh"
#include "generated/example.ecsact.hh"
#include "simulation_config.hh"

SDL_Renderer* renderer;
int           viewport_width;
int           viewport_height;

static auto SDLCALL notify_system_execution_thread(void* data) -> int {
	int  cnt;
	auto ev = SDL_Event{};
	ev.type = SDL_USEREVENT;
	while(!*static_cast<bool*>(data) /* done bool */) {
		SDL_PushEvent(&ev);
		SDL_Delay(
			static_cast<int>(example::simulation_config::fixed_delta_time * 1000.f)
		);
	}

	return 0;
}

static auto key_actions( //
	SDL_KeyboardEvent                ev,
	ecsact::core::execution_options& exec_options
) -> void {
	// NOTE: we need to maintain the lifecyle of these actions so we use global
	// storage
	static auto move = example::Move{};
	static auto jump = example::Jump{};
	static auto fire = example::Fire{};
	static auto reverse_gravity = example::ReverseGravity{};

	const auto pressed = ev.state == SDL_PRESSED;

	if(pressed && ev.repeat > 0) {
		return;
	}

	if(ev.keysym.sym == SDLK_w) {
		move.dir_y += pressed ? 1.0f : -1.0f;
		return exec_options.push_action(&move);
	}

	if(ev.keysym.sym == SDLK_a) {
		move.dir_x -= pressed ? 1.0f : -1.0f;
		return exec_options.push_action(&move);
	}

	if(ev.keysym.sym == SDLK_s) {
		move.dir_y -= pressed ? 1.0f : -1.0f;
		return exec_options.push_action(&move);
	}

	if(ev.keysym.sym == SDLK_d) {
		move.dir_x += pressed ? 1.0f : -1.0f;
		return exec_options.push_action(&move);
	}

	if(pressed && ev.keysym.sym == SDLK_r) {
		return exec_options.push_action(&reverse_gravity);
	}

	if(pressed && ev.keysym.sym == SDLK_j) {
		return exec_options.push_action(&fire);
	}

	if(pressed && ev.keysym.sym == SDLK_SPACE) {
		return exec_options.push_action(&jump);
	}
}

auto main(int argc, char* argv[]) -> int {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	// TODO(Kelwan): Make Tracy conditional
	tracy::StartupProfiler();

	// TODO: Create codegen for this
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::Move::id),
		&example__Move
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::Movement::id),
		&example__Movement
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::PhysicsParent::id),
		&example__PhysicsParent
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::PhysicsParent::Physics::id),
		&example__PhysicsParent__Physics
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::Jump::id),
		&example__Jump
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::ApplyVelocity::id),
		&example__ApplyVelocity
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::Render::id),
		&example__Render
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::RenderAimer::id),
		&example__RenderAimer
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::ViewportCollision::id),
		&example__ViewportCollision
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::Fire::id),
		&example__Fire
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::ReverseGravity::id),
		&example__ReverseGravity
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::CollisionParent::id),
		&example__CollisionParent
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(
			example::CollisionParent::Collision::id
		),
		&example__CollisionParent__Collision
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::AlwaysRemoveColliding::id),
		&example__AlwaysRemoveColliding
	);
	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::CollisionPressurePush::id),
		&example__CollisionPressurePush
	);

	auto done = false;
	auto reg = ecsact::core::registry{"C++ SDL2"};
	auto win = SDL_CreateWindow(
		"Ecsact Example - C++ SDL2",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		0
	);

	if(win == nullptr) {
		SDL_Log("failed to create window: %s", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(win, -1, 0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	if(!ImGui_ImplSDL2_InitForSDLRenderer(win, renderer)) {
		SDL_Log("failed to init imgui for sdlrenderer2");
		return 1;
	}
	if(!ImGui_ImplSDLRenderer2_Init(renderer)) {
		SDL_Log("failed to init imgui sdlrenderer2");
		return 1;
	}

	SDL_RegisterEvents(1);
	auto exec_thread = SDL_CreateThread(
		notify_system_execution_thread,
		"Ecsact System Execution Ticker",
		&done
	);

	auto exec_options = ecsact::core::execution_options{};
	auto evc = ecsact::core::execution_events_collector<>{};

	auto create_entity_events_fired = 0;
	auto destroy_entity_events_fired = 0;
	auto init_events_fired = 0;
	auto update_events_fired = 0;
	auto remove_events_fired = 0;

	evc.set_any_init_callback([&](auto, const auto&) { init_events_fired += 1; });
	evc.set_any_update_callback([&](auto, const auto&) {
		update_events_fired += 1;
	});
	evc.set_any_remove_callback([&](auto, const auto&) {
		remove_events_fired += 1;
	});

	// NOTE: created/destroyed callback being called too often
	evc.set_entity_created_callback([&](auto, auto) {
		create_entity_events_fired += 1;
	});
	evc.set_entity_destroyed_callback([&](auto) {
		destroy_entity_events_fired -= 1;
	});

	auto physics_singleton = reg.create_entity();
	reg.add_component(physics_singleton, example::Gravity{9810.f});

	auto player_entity = reg.create_entity();
	reg.add_component<example::Player>(player_entity);
	reg.add_component(player_entity, example::Moving{});
	reg.add_component(player_entity, example::Position{});
	reg.add_component(player_entity, example::Velocity{});

	SDL_GetWindowSize(win, &viewport_width, &viewport_height);

	auto last_ticks = SDL_GetTicks64();
	auto execution_count = 0;
	auto event = SDL_Event{};
	while(!done && SDL_WaitEvent(&event) == 1) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		if(event.type == SDL_QUIT) {
			done = true;
			break;
		} else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			key_actions(event.key, exec_options);
		} else if(event.type == SDL_USEREVENT) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			ImGui_ImplSDLRenderer2_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Details");
			ImGui::Text("Execution Count: %i", execution_count);
			ImGui::Text("Entity Count (api): %i", reg.count_entities());
			ImGui::Text("Create Entity Events: %i", create_entity_events_fired);
			ImGui::Text("Destroy Entity Events: %i", destroy_entity_events_fired);
			ImGui::Text("Init Events: %i", init_events_fired);
			ImGui::Text("Update Events: %i", update_events_fired);
			ImGui::Text("Remove Events: %i", remove_events_fired);

			auto before_exec = SDL_GetTicks64();
			auto err = reg.execute_systems(std::array{exec_options}, evc);
			auto after_exec = SDL_GetTicks64();
			ImGui::Text("Execute Systems Time: %llums", after_exec - before_exec);
			execution_count += 1;
			ImGui::End();
			if(err != ECSACT_EXEC_SYS_OK) {
				SDL_LogError(
					SDL_LOG_CATEGORY_APPLICATION,
					"System Execution Failure %i",
					err
				);
				done = true;
				break;
			}
			exec_options.clear();

			ImGui::Render();
			ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
			SDL_RenderPresent(renderer);
			FrameMark;
		} else if(event.type == SDL_WINDOWEVENT) {
			if(event.window.type == SDL_WINDOWEVENT_RESIZED) {
				SDL_GetWindowSize(win, &viewport_width, &viewport_height);
			}
		}
	}

	SDL_WaitThread(exec_thread, nullptr);
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_Quit();
	tracy::ShutdownProfiler();
	return 0;
}
