// GENERATED FILE - DO NOT EDIT
#include "EcsactUnrealFps.ecsact.systems.hh"
void example__fps__Fire (struct ecsact_system_execution_context* cctx) {
	example::fps::Fire::context ctx{cctx};
	example::fps::Fire::impl(ctx);
}
void example__fps__StartFiring (struct ecsact_system_execution_context* cctx) {
	example::fps::StartFiring::context ctx{cctx};
	example::fps::StartFiring::impl(ctx);
}
void example__fps__StopFiring (struct ecsact_system_execution_context* cctx) {
	example::fps::StopFiring::context ctx{cctx};
	example::fps::StopFiring::impl(ctx);
}
