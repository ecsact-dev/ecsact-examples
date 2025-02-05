// GENERATED FILE - DO NOT EDIT
#pragma once

#include <type_traits>
#include "ecsact/cpp/execution_context.hh"
#include "Floppybots.ecsact.hh"
#include "Floppybots.ecsact.systems.h"


struct ecsact_system_execution_context;

struct floppybots::StunTimer::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.StunTimer context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- floppybots.Stunned\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.StunTimer context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Stunned\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.StunTimer context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.StunnedExpired\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.StunTimer context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.StunnedExpired\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Stunned>() -> floppybots::Stunned {
		return _ctx.get<floppybots::Stunned>();
	}
	template<> auto add<floppybots::StunnedExpired>() -> void {
		_ctx.add<floppybots::StunnedExpired>();
	}
	template<> auto update<floppybots::Stunned>(const floppybots::Stunned& updated_component) -> void {
		_ctx.update<floppybots::Stunned>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::PusherExpireChecker::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.PusherExpireChecker context.get<T> may only be called with a\n"
		"| component readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- floppybots.Pusher\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.PusherExpireChecker context.update<T> may only be called with a\n"
		"| component writable by the system. Did you forget to add readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- floppybots.Pusher\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.PusherExpireChecker context.add<T> may only be called with a\n"
		"| component addable by the system. Did you forget to add adds capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.PusherExpired\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.PusherExpireChecker context.add<T> may only be called with a\n"
		"| component addable by the system. Did you forget to add adds capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.PusherExpired\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Pusher>() -> floppybots::Pusher {
		return _ctx.get<floppybots::Pusher>();
	}
	template<> auto add<floppybots::PusherExpired>() -> void {
		_ctx.add<floppybots::PusherExpired>();
	}
	template<> auto update<floppybots::Pusher>(const floppybots::Pusher& updated_component) -> void {
		_ctx.update<floppybots::Pusher>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::PusherApplyExpired::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto remove(AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.PusherApplyExpired context.remove<T> may only be called with a\n"
		"| component removable by the system. Did you forget to add removes capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Pusher\n"
		"| \n");
	}
	
	template<> auto remove<floppybots::Pusher>() -> void {
		return _ctx.remove<floppybots::Pusher>();
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::FinishPush::PushEntities::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.FinishPush.PushEntities context.get<T> may only be called with a\n"
		"| component readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- floppybots.Position\n"
		"| 	- floppybots.Enemy\n"
		"| 	- floppybots.Toggle\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.FinishPush.PushEntities context.update<T> may only be called with\n"
		"| a component writable by the system. Did you forget to add readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- floppybots.Enemy\n"
		"| 	- floppybots.Toggle\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.FinishPush.PushEntities context.add<T> may only be called with a\n"
		"| component addable by the system. Did you forget to add adds capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Pushing\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.FinishPush.PushEntities context.add<T> may only be called with a\n"
		"| component addable by the system. Did you forget to add adds capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Pushing\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Position>() -> floppybots::Position {
		return _ctx.get<floppybots::Position>();
	}
	template<> auto get<floppybots::Enemy>() -> floppybots::Enemy {
		return _ctx.get<floppybots::Enemy>();
	}
	template<> auto get<floppybots::Toggle>() -> floppybots::Toggle {
		return _ctx.get<floppybots::Toggle>();
	}
	template<> auto add<floppybots::Pushing>(const floppybots::Pushing& new_component) -> void {
		_ctx.add<floppybots::Pushing>(new_component);
	}
	template<> auto update<floppybots::Enemy>(const floppybots::Enemy& updated_component) -> void {
		_ctx.update<floppybots::Enemy>(updated_component);
	}
	template<> auto update<floppybots::Toggle>(const floppybots::Toggle& updated_component) -> void {
		_ctx.update<floppybots::Toggle>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	const floppybots::FinishPush::context parent() const;
	
	
	
};

struct floppybots::RemovePushCharge::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto remove(AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.RemovePushCharge context.remove<T> may only be called with a\n"
		"| component removable by the system. Did you forget to add removes capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.PushCharge\n"
		"| \n");
	}
	
	template<> auto remove<floppybots::PushCharge>() -> void {
		return _ctx.remove<floppybots::PushCharge>();
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::TickPushCharge::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.TickPushCharge context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- floppybots.Player\n"
		"| 	- floppybots.PushCharge\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.TickPushCharge context.update<T> may only be called with a\n"
		"| component writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.PushCharge\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Player>() -> floppybots::Player {
		return _ctx.get<floppybots::Player>();
	}
	template<> auto get<floppybots::PushCharge>() -> floppybots::PushCharge {
		return _ctx.get<floppybots::PushCharge>();
	}
	template<> auto update<floppybots::PushCharge>(const floppybots::PushCharge& updated_component) -> void {
		_ctx.update<floppybots::PushCharge>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::ApplyPush::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ApplyPush context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- floppybots.Velocity\n"
		"| 	- floppybots.Pushing\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ApplyPush context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Velocity\n"
		"| 	- floppybots.Pushing\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Velocity>() -> floppybots::Velocity {
		return _ctx.get<floppybots::Velocity>();
	}
	template<> auto get<floppybots::Pushing>() -> floppybots::Pushing {
		return _ctx.get<floppybots::Pushing>();
	}
	template<> auto update<floppybots::Velocity>(const floppybots::Velocity& updated_component) -> void {
		_ctx.update<floppybots::Velocity>(updated_component);
	}
	template<> auto update<floppybots::Pushing>(const floppybots::Pushing& updated_component) -> void {
		_ctx.update<floppybots::Pushing>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::ApplyVelocity::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ApplyVelocity context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- floppybots.Position\n"
		"| 	- floppybots.Velocity\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ApplyVelocity context.update<T> may only be called with a\n"
		"| component writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Position\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Position>() -> floppybots::Position {
		return _ctx.get<floppybots::Position>();
	}
	template<> auto get<floppybots::Velocity>() -> floppybots::Velocity {
		return _ctx.get<floppybots::Velocity>();
	}
	template<> auto update<floppybots::Position>(const floppybots::Position& updated_component) -> void {
		_ctx.update<floppybots::Position>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::ApplyDrag::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ApplyDrag context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- floppybots.Velocity\n"
		"| 	- floppybots.Pushing\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ApplyDrag context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Velocity\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ApplyDrag context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.Stunned\n"
		"| 	- floppybots.RemovePushingTag\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ApplyDrag context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.Stunned\n"
		"| 	- floppybots.RemovePushingTag\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Velocity>() -> floppybots::Velocity {
		return _ctx.get<floppybots::Velocity>();
	}
	template<> auto get<floppybots::Pushing>() -> floppybots::Pushing {
		return _ctx.get<floppybots::Pushing>();
	}
	template<> auto add<floppybots::Stunned>(const floppybots::Stunned& new_component) -> void {
		_ctx.add<floppybots::Stunned>(new_component);
	}
	template<> auto add<floppybots::RemovePushingTag>() -> void {
		_ctx.add<floppybots::RemovePushingTag>();
	}
	template<> auto update<floppybots::Velocity>(const floppybots::Velocity& updated_component) -> void {
		_ctx.update<floppybots::Velocity>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::ResumeStreaming::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ResumeStreaming context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- floppybots.Toggle\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.ResumeStreaming context.update<T> may only be called with a\n"
		"| component writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Toggle\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Toggle>() -> floppybots::Toggle {
		return _ctx.get<floppybots::Toggle>();
	}
	template<> auto update<floppybots::Toggle>(const floppybots::Toggle& updated_component) -> void {
		_ctx.update<floppybots::Toggle>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::TogglePushedEntities::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.TogglePushedEntities context.get<T> may only be called with a\n"
		"| component readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- floppybots.Toggle\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto stream_toggle(bool stream_enable, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.TogglePushedEntities context.stream_toggle<T> may only be called\n"
		"| with stream components declared by the system. Did you forget to add stream\n"
		"| toggle capabilities? The following components are allowed:\n"
		"| 	- floppybots.Rotation\n"
		"| 	- floppybots.Position\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Toggle>() -> floppybots::Toggle {
		return _ctx.get<floppybots::Toggle>();
	}
	template<> auto stream_toggle<floppybots::Rotation>(bool enable_stream) -> void {
		return _ctx.stream_toggle<floppybots::Rotation>(enable_stream);
		
	}
	template<> auto stream_toggle<floppybots::Position>(bool enable_stream) -> void {
		return _ctx.stream_toggle<floppybots::Position>(enable_stream);
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::RemovePushing::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto remove(AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.RemovePushing context.remove<T> may only be called with a\n"
		"| component removable by the system. Did you forget to add removes capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Pushing\n"
		"| 	- floppybots.RemovePushingTag\n"
		"| \n");
	}
	
	template<> auto remove<floppybots::Pushing>() -> void {
		return _ctx.remove<floppybots::Pushing>();
		
	}
	template<> auto remove<floppybots::RemovePushingTag>() -> void {
		return _ctx.remove<floppybots::RemovePushingTag>();
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::StunnedExpiry::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto remove(AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.StunnedExpiry context.remove<T> may only be called with a\n"
		"| component removable by the system. Did you forget to add removes capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Stunned\n"
		"| 	- floppybots.StunnedExpired\n"
		"| \n");
	}
	
	template<> auto remove<floppybots::Stunned>() -> void {
		return _ctx.remove<floppybots::Stunned>();
		
	}
	template<> auto remove<floppybots::StunnedExpired>() -> void {
		return _ctx.remove<floppybots::StunnedExpired>();
		
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};

struct floppybots::StartPush::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.StartPush context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- floppybots.Player\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.StartPush context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.PushCharge\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.StartPush context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.PushCharge\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Player>() -> floppybots::Player {
		return _ctx.get<floppybots::Player>();
	}
	template<> auto add<floppybots::PushCharge>(const floppybots::PushCharge& new_component) -> void {
		_ctx.add<floppybots::PushCharge>(new_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> floppybots::StartPush {
		return _ctx.action<floppybots::StartPush>();
	}
	
};

struct floppybots::FinishPush::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.FinishPush context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite capabilities?\n"
		"| The following components are allowed:\n"
		"| 	- floppybots.Player\n"
		"| 	- floppybots.Position\n"
		"| 	- floppybots.PushCharge\n"
		"| \n");
	}
	
	template<typename T>
		requires(!std::is_empty_v<T>)
	auto add(const T& new_component) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.FinishPush context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.Pusher\n"
		"| \n");
	}
	template<typename T>
	auto add() -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.FinishPush context.add<T> may only be called with a component\n"
		"| addable by the system. Did you forget to add adds capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.Pusher\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Player>() -> floppybots::Player {
		return _ctx.get<floppybots::Player>();
	}
	template<> auto get<floppybots::Position>() -> floppybots::Position {
		return _ctx.get<floppybots::Position>();
	}
	template<> auto get<floppybots::PushCharge>() -> floppybots::PushCharge {
		return _ctx.get<floppybots::PushCharge>();
	}
	template<> auto add<floppybots::Pusher>(const floppybots::Pusher& new_component) -> void {
		_ctx.add<floppybots::Pusher>(new_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> floppybots::FinishPush {
		return _ctx.action<floppybots::FinishPush>();
	}
	
};

struct floppybots::Move::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.Move context.get<T> may only be called with a component readable\n"
		"| by the system. Did you forget to add readonly or readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- floppybots.Player\n"
		"| 	- floppybots.MoveDirection\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| floppybots.Move context.update<T> may only be called with a component\n"
		"| writable by the system. Did you forget to add readwrite capabilities? The following\n"
		"| components are allowed:\n"
		"| 	- floppybots.MoveDirection\n"
		"| \n");
	}
	
	template<> auto get<floppybots::Player>() -> floppybots::Player {
		return _ctx.get<floppybots::Player>();
	}
	template<> auto get<floppybots::MoveDirection>() -> floppybots::MoveDirection {
		return _ctx.get<floppybots::MoveDirection>();
	}
	template<> auto update<floppybots::MoveDirection>(const floppybots::MoveDirection& updated_component) -> void {
		_ctx.update<floppybots::MoveDirection>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	auto action() const -> floppybots::Move {
		return _ctx.action<floppybots::Move>();
	}
	
};
