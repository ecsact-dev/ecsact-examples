// GENERATED FILE - DO NOT EDIT
#pragma once

#include <type_traits>
#include "ecsact/cpp/execution_context.hh"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps.ecsact.systems.h"


struct ecsact_system_execution_context;

struct example::fps::Fire::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
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
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.Fire context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.Player\n"
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
	template<> auto update<example::fps::Player>(const example::fps::Player& updated_component) -> void {
		_ctx.update<example::fps::Player>(updated_component);
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
	
	
	
};

struct example::fps::StartFiring::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StartFiring context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- example.fps.Player\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StartFiring context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.Firing\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StartFiring context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.Firing\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto stream_toggle(bool stream_enable, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StartFiring context.stream_toggle<T> may only be called with\n"
		"| stream components declared by the system. Did you forget to add stream toggle\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- example.fps.Rotation\n"
		"| 	- example.fps.Position\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Player>() -> example::fps::Player {
		return _ctx.get<example::fps::Player>();
	}
	template<> auto add<example::fps::Firing>(const example::fps::Firing& new_component) -> void {
		_ctx.add<example::fps::Firing>(new_component);
	}
	template<> auto stream_toggle<example::fps::Rotation>(bool enable_stream) -> void {
		return _ctx.stream_toggle<example::fps::Rotation>(enable_stream);
		
	}
	template<> auto stream_toggle<example::fps::Position>(bool enable_stream) -> void {
		return _ctx.stream_toggle<example::fps::Position>(enable_stream);
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> example::fps::StartFiring {
		return _ctx.action<example::fps::StartFiring>();
	}
	
};

struct example::fps::StopFiring::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StopFiring context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- example.fps.Player\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto remove(AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StopFiring context.remove<T> may only be called with a component\n"
		"| removable by the system. Did you forget to add removes capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Firing\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto stream_toggle(bool stream_enable, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StopFiring context.stream_toggle<T> may only be called with\n"
		"| stream components declared by the system. Did you forget to add stream toggle\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- example.fps.Rotation\n"
		"| 	- example.fps.Position\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Player>() -> example::fps::Player {
		return _ctx.get<example::fps::Player>();
	}
	template<> auto remove<example::fps::Firing>() -> void {
		return _ctx.remove<example::fps::Firing>();
		
	}
	template<> auto stream_toggle<example::fps::Rotation>(bool enable_stream) -> void {
		return _ctx.stream_toggle<example::fps::Rotation>(enable_stream);
		
	}
	template<> auto stream_toggle<example::fps::Position>(bool enable_stream) -> void {
		return _ctx.stream_toggle<example::fps::Position>(enable_stream);
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> example::fps::StopFiring {
		return _ctx.action<example::fps::StopFiring>();
	}
	
};
