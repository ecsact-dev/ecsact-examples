#include "SystemImpls.h"
#include "EcsactUnrealCppBasic/Example.ecsact.systems.h"
#include "Example.ecsact.hh"
#include "ecsact/runtime/dynamic.h"
#include <iterator>

#ifndef ECSACT_DYNAMIC_API_LOAD_AT_RUNTIME
#	error "ECSACT_DYNAMIC_API_LOAD_AT_RUNTIME must be defined"
#endif

auto example::Gravity::impl(context& ctx) -> void {
}

auto example::FloorBounce::impl(context& ctx) -> void {
}

auto example::ApplyVelocity::impl(context& ctx) -> void {
}

auto USystemImpls::RunnerStart_Implementation(class UEcsactRunner*) -> void {
	// Here we are manually setting our system implementations one by one. In your
	// application it is preferred to automate this step with a codegen plugin or
	// have your systems embedded into your runtime.
	// For simplicity this will do just fine.

	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::ApplyVelocity::id),
		&example__ApplyVelocity
	);

	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::Gravity::id),
		&example__Gravity
	);

	ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(example::FloorBounce::id),
		&example__FloorBounce
	);
}
