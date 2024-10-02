// GENERATED FILE - DO NOT EDIT
#pragma once

#include <type_traits>
#include "ecsact/cpp/execution_context.hh"
#include "Example.ecsact.hh"
#include "Example.ecsact.systems.h"


struct ecsact_system_execution_context;

struct example::Gravity::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T>
	auto get() -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.Gravity context.get<T> may only be called with a component readable\n"
		"| by the system. Did you forget to add readonly or readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.Velocity\n"
		"| \n");
	}
	
	template<typename T>
	auto update(const T& updated_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.Gravity context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.Velocity\n"
		"| \n");
	}
	
	template<> auto get<example::Velocity>() -> example::Velocity {
		return _ctx.get<example::Velocity>();
	}
	template<> auto update<example::Velocity>(const example::Velocity& updated_component) -> void {
		_ctx.update<example::Velocity>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::FloorBounce::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T>
	auto get() -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.FloorBounce context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.Position\n"
		"| 	- example.Velocity\n"
		"| \n");
	}
	
	template<typename T>
	auto update(const T& updated_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.FloorBounce context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.Velocity\n"
		"| \n");
	}
	
	template<> auto get<example::Position>() -> example::Position {
		return _ctx.get<example::Position>();
	}
	template<> auto get<example::Velocity>() -> example::Velocity {
		return _ctx.get<example::Velocity>();
	}
	template<> auto update<example::Velocity>(const example::Velocity& updated_component) -> void {
		_ctx.update<example::Velocity>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::ApplyVelocity::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T>
	auto get() -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.ApplyVelocity context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- example.Position\n"
		"| 	- example.Velocity\n"
		"| \n");
	}
	
	template<typename T>
	auto update(const T& updated_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.ApplyVelocity context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.Position\n"
		"| \n");
	}
	
	template<> auto get<example::Position>() -> example::Position {
		return _ctx.get<example::Position>();
	}
	template<> auto get<example::Velocity>() -> example::Velocity {
		return _ctx.get<example::Velocity>();
	}
	template<> auto update<example::Position>(const example::Position& updated_component) -> void {
		_ctx.update<example::Position>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};
