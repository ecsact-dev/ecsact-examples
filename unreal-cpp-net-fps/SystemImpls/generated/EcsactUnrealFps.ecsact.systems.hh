// GENERATED FILE - DO NOT EDIT
#pragma once

#include <type_traits>
#include "ecsact/cpp/execution_context.hh"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps.ecsact.systems.h"


struct ecsact_system_execution_context;

struct example::fps::PusherExpireChecker::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.PusherExpireChecker context.get<T> may only be called with a\n"
		"| component readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- example.fps.Pusher\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.PusherExpireChecker context.update<T> may only be called with a\n"
		"| component writable by the system. Did you forget to add readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- example.fps.Pusher\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.PusherExpireChecker context.add<T> may only be called with a\n"
		"| component addable by the system. Did you forget to add adds capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.PusherExpired\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.PusherExpireChecker context.add<T> may only be called with a\n"
		"| component addable by the system. Did you forget to add adds capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.PusherExpired\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Pusher>() -> example::fps::Pusher {
		return _ctx.get<example::fps::Pusher>();
	}
	template<> auto add<example::fps::PusherExpired>() -> void {
		_ctx.add<example::fps::PusherExpired>();
	}
	template<> auto update<example::fps::Pusher>(const example::fps::Pusher& updated_component) -> void {
		_ctx.update<example::fps::Pusher>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::PusherApplyExpired::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto remove(AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.PusherApplyExpired context.remove<T> may only be called with a\n"
		"| component removable by the system. Did you forget to add removes capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- example.fps.Pusher\n"
		"| \n");
	}
	
	template<> auto remove<example::fps::Pusher>() -> void {
		return _ctx.remove<example::fps::Pusher>();
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::FinishPush::PushEntities::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.FinishPush.PushEntities context.get<T> may only be called with a\n"
		"| component readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- example.fps.Position\n"
		"| 	- example.fps.Toggle\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.FinishPush.PushEntities context.update<T> may only be called with\n"
		"| a component writable by the system. Did you forget to add readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- example.fps.Toggle\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.FinishPush.PushEntities context.add<T> may only be called with a\n"
		"| component addable by the system. Did you forget to add adds capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Pushing\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.FinishPush.PushEntities context.add<T> may only be called with a\n"
		"| component addable by the system. Did you forget to add adds capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Pushing\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Position>() -> example::fps::Position {
		return _ctx.get<example::fps::Position>();
	}
	template<> auto get<example::fps::Toggle>() -> example::fps::Toggle {
		return _ctx.get<example::fps::Toggle>();
	}
	template<> auto add<example::fps::Pushing>(const example::fps::Pushing& new_component) -> void {
		_ctx.add<example::fps::Pushing>(new_component);
	}
	template<> auto update<example::fps::Toggle>(const example::fps::Toggle& updated_component) -> void {
		_ctx.update<example::fps::Toggle>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	const example::fps::FinishPush::context parent() const;
	
	
	
};

struct example::fps::RemovePushCharge::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto remove(AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.RemovePushCharge context.remove<T> may only be called with a\n"
		"| component removable by the system. Did you forget to add removes capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.PushCharge\n"
		"| \n");
	}
	
	template<> auto remove<example::fps::PushCharge>() -> void {
		return _ctx.remove<example::fps::PushCharge>();
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::TickPushCharge::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.TickPushCharge context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- example.fps.Player\n"
		"| 	- example.fps.PushCharge\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.TickPushCharge context.update<T> may only be called with a\n"
		"| component writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.PushCharge\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Player>() -> example::fps::Player {
		return _ctx.get<example::fps::Player>();
	}
	template<> auto get<example::fps::PushCharge>() -> example::fps::PushCharge {
		return _ctx.get<example::fps::PushCharge>();
	}
	template<> auto update<example::fps::PushCharge>(const example::fps::PushCharge& updated_component) -> void {
		_ctx.update<example::fps::PushCharge>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::ApplyPush::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.ApplyPush context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- example.fps.Velocity\n"
		"| 	- example.fps.Pushing\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.ApplyPush context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Velocity\n"
		"| 	- example.fps.Pushing\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Velocity>() -> example::fps::Velocity {
		return _ctx.get<example::fps::Velocity>();
	}
	template<> auto get<example::fps::Pushing>() -> example::fps::Pushing {
		return _ctx.get<example::fps::Pushing>();
	}
	template<> auto update<example::fps::Velocity>(const example::fps::Velocity& updated_component) -> void {
		_ctx.update<example::fps::Velocity>(updated_component);
	}
	template<> auto update<example::fps::Pushing>(const example::fps::Pushing& updated_component) -> void {
		_ctx.update<example::fps::Pushing>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::ApplyVelocity::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.ApplyVelocity context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- example.fps.Position\n"
		"| 	- example.fps.Velocity\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.ApplyVelocity context.update<T> may only be called with a\n"
		"| component writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Position\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Position>() -> example::fps::Position {
		return _ctx.get<example::fps::Position>();
	}
	template<> auto get<example::fps::Velocity>() -> example::fps::Velocity {
		return _ctx.get<example::fps::Velocity>();
	}
	template<> auto update<example::fps::Position>(const example::fps::Position& updated_component) -> void {
		_ctx.update<example::fps::Position>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::ApplyDrag::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.ApplyDrag context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- example.fps.Velocity\n"
		"| 	- example.fps.Pushing\n"
		"| 	- example.fps.Toggle\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.ApplyDrag context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Velocity\n"
		"| 	- example.fps.Toggle\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.ApplyDrag context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.RemovePushingTag\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.ApplyDrag context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.RemovePushingTag\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Velocity>() -> example::fps::Velocity {
		return _ctx.get<example::fps::Velocity>();
	}
	template<> auto get<example::fps::Pushing>() -> example::fps::Pushing {
		return _ctx.get<example::fps::Pushing>();
	}
	template<> auto get<example::fps::Toggle>() -> example::fps::Toggle {
		return _ctx.get<example::fps::Toggle>();
	}
	template<> auto add<example::fps::RemovePushingTag>() -> void {
		_ctx.add<example::fps::RemovePushingTag>();
	}
	template<> auto update<example::fps::Velocity>(const example::fps::Velocity& updated_component) -> void {
		_ctx.update<example::fps::Velocity>(updated_component);
	}
	template<> auto update<example::fps::Toggle>(const example::fps::Toggle& updated_component) -> void {
		_ctx.update<example::fps::Toggle>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::TogglePushedEntities::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.TogglePushedEntities context.get<T> may only be called with a\n"
		"| component readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- example.fps.Toggle\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto stream_toggle(bool stream_enable, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.TogglePushedEntities context.stream_toggle<T> may only be called\n"
		"| with stream components declared by the system. Did you forget to add stream\n"
		"| toggle capabilities? The following components are allowed:\n"
		"| 	- example.fps.Position\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Toggle>() -> example::fps::Toggle {
		return _ctx.get<example::fps::Toggle>();
	}
	template<> auto stream_toggle<example::fps::Position>(bool enable_stream) -> void {
		return _ctx.stream_toggle<example::fps::Position>(enable_stream);
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::RemovePushing::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto remove(AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.RemovePushing context.remove<T> may only be called with a\n"
		"| component removable by the system. Did you forget to add removes capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Pushing\n"
		"| 	- example.fps.RemovePushingTag\n"
		"| \n");
	}
	
	template<> auto remove<example::fps::Pushing>() -> void {
		return _ctx.remove<example::fps::Pushing>();
		
	}
	template<> auto remove<example::fps::RemovePushingTag>() -> void {
		return _ctx.remove<example::fps::RemovePushingTag>();
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct example::fps::StartPush::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StartPush context.get<T> may only be called with a component\n"
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
		"| example.fps.StartPush context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.PushCharge\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.StartPush context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.PushCharge\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Player>() -> example::fps::Player {
		return _ctx.get<example::fps::Player>();
	}
	template<> auto add<example::fps::PushCharge>(const example::fps::PushCharge& new_component) -> void {
		_ctx.add<example::fps::PushCharge>(new_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> example::fps::StartPush {
		return _ctx.action<example::fps::StartPush>();
	}
	
};

struct example::fps::FinishPush::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.FinishPush context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- example.fps.Player\n"
		"| 	- example.fps.Position\n"
		"| 	- example.fps.PushCharge\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.FinishPush context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.Pusher\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.FinishPush context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.Pusher\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Player>() -> example::fps::Player {
		return _ctx.get<example::fps::Player>();
	}
	template<> auto get<example::fps::Position>() -> example::fps::Position {
		return _ctx.get<example::fps::Position>();
	}
	template<> auto get<example::fps::PushCharge>() -> example::fps::PushCharge {
		return _ctx.get<example::fps::PushCharge>();
	}
	template<> auto add<example::fps::Pusher>(const example::fps::Pusher& new_component) -> void {
		_ctx.add<example::fps::Pusher>(new_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> example::fps::FinishPush {
		return _ctx.action<example::fps::FinishPush>();
	}
	
};

struct example::fps::Move::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.Move context.get<T> may only be called with a component readable\n"
		"| by the system. Did you forget to add readonly or readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- example.fps.Player\n"
		"| 	- example.fps.MoveDirection\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| example.fps.Move context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- example.fps.MoveDirection\n"
		"| \n");
	}
	
	template<> auto get<example::fps::Player>() -> example::fps::Player {
		return _ctx.get<example::fps::Player>();
	}
	template<> auto get<example::fps::MoveDirection>() -> example::fps::MoveDirection {
		return _ctx.get<example::fps::MoveDirection>();
	}
	template<> auto update<example::fps::MoveDirection>(const example::fps::MoveDirection& updated_component) -> void {
		_ctx.update<example::fps::MoveDirection>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> example::fps::Move {
		return _ctx.action<example::fps::Move>();
	}
	
};
