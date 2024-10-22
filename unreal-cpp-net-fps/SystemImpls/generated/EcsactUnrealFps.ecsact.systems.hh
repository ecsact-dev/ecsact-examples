// GENERATED FILE - DO NOT EDIT
#pragma once

#include <type_traits>
#include "ecsact/cpp/execution_context.hh"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps.ecsact.systems.h"


struct ecsact_system_execution_context;

struct example::fps::Fire::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T>
	auto get() -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.Fire context.get<T> may only be called with a component readable\n"
		"| by the system. Did you forget to add readonly or readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Player\n"
		"| 	- example.fps.Rotation\n"
		"| 	- example.fps.Position\n"
		"| \n");
	}
	
	template<typename T>
	auto update(const T& updated_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.Fire context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.Rotation\n"
		"| 	- example.fps.Position\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Player>() -> example::fps::Player {
		return _ctx.get<example::fps::Player>();
	}
	template<> auto get<example::fps::Rotation>() -> example::fps::Rotation {
		return _ctx.get<example::fps::Rotation>();
	}
	template<> auto get<example::fps::Position>() -> example::fps::Position {
		return _ctx.get<example::fps::Position>();
	}
	template<> auto update<example::fps::Rotation>(const example::fps::Rotation& updated_component) -> void {
		_ctx.update<example::fps::Rotation>(updated_component);
	}
	template<> auto update<example::fps::Position>(const example::fps::Position& updated_component) -> void {
		_ctx.update<example::fps::Position>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> example::fps::Fire {
		return _ctx.action<example::fps::Fire>();
	}
	
};
