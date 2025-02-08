// GENERATED FILE - DO NOT EDIT
#pragma once

#include <type_traits>
#include "ecsact/cpp/execution_context.hh"
#include "EcsactBenchmark.ecsact.hh"
#include "EcsactBenchmark.ecsact.systems.h"


struct ecsact_system_execution_context;

struct benchmark::IterateCounter::context {
	[[no_unique_address]] ::ecsact::execution_context _ctx;
	
	template<typename T, typename... AssocFields>
	auto get(AssocFields&&... assoc_fields) -> T {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| benchmark.IterateCounter context.get<T> may only be called with a component\n"
		"| readable by the system. Did you forget to add readonly or readwrite\n"
		"| capabilities? The following components are allowed:\n"
		"| 	- benchmark.Counter\n"
		"| \n");
	}
	
	template<typename T, typename... AssocFields>
	auto update(const T& updated_component, AssocFields&&... assoc_fields) -> void {
		// local type to make static assert always fail
		struct codegen_error {};
		static_assert(std::is_same_v<T, codegen_error>, 
		"| [Ecsact C++ Error]: System Execution Context Misuse\n"
		"| benchmark.IterateCounter context.update<T> may only be called with a\n"
		"| component writable by the system. Did you forget to add readwrite capabilities? The\n"
		"| following components are allowed:\n"
		"| 	- benchmark.Counter\n"
		"| \n");
	}
	
	template<> auto get<benchmark::Counter>() -> benchmark::Counter {
		return _ctx.get<benchmark::Counter>();
	}
	template<> auto update<benchmark::Counter>(const benchmark::Counter& updated_component) -> void {
		_ctx.update<benchmark::Counter>(updated_component);
	}
	auto entity() const -> ecsact_entity_id {
		return _ctx.entity();
	}
	
	
	
};
