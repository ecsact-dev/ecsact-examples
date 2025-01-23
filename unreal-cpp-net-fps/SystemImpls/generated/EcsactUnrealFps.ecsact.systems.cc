// GENERATED FILE - DO NOT EDIT
#include "EcsactUnrealFps.ecsact.systems.hh"
void example__fps__StunTimer (struct ecsact_system_execution_context* cctx) {
	example::fps::StunTimer::context ctx{cctx};
	example::fps::StunTimer::impl(ctx);
}
void example__fps__PusherExpireChecker (struct ecsact_system_execution_context* cctx) {
	example::fps::PusherExpireChecker::context ctx{cctx};
	example::fps::PusherExpireChecker::impl(ctx);
}
void example__fps__PusherApplyExpired (struct ecsact_system_execution_context* cctx) {
	example::fps::PusherApplyExpired::context ctx{cctx};
	example::fps::PusherApplyExpired::impl(ctx);
}
void example__fps__FinishPush__PushEntities (struct ecsact_system_execution_context* cctx) {
	example::fps::FinishPush::PushEntities::context ctx{cctx};
	example::fps::FinishPush::PushEntities::impl(ctx);
}
void example__fps__RemovePushCharge (struct ecsact_system_execution_context* cctx) {
	example::fps::RemovePushCharge::context ctx{cctx};
	example::fps::RemovePushCharge::impl(ctx);
}
void example__fps__TickPushCharge (struct ecsact_system_execution_context* cctx) {
	example::fps::TickPushCharge::context ctx{cctx};
	example::fps::TickPushCharge::impl(ctx);
}
void example__fps__ApplyPush (struct ecsact_system_execution_context* cctx) {
	example::fps::ApplyPush::context ctx{cctx};
	example::fps::ApplyPush::impl(ctx);
}
void example__fps__ApplyVelocity (struct ecsact_system_execution_context* cctx) {
	example::fps::ApplyVelocity::context ctx{cctx};
	example::fps::ApplyVelocity::impl(ctx);
}
void example__fps__ApplyDrag (struct ecsact_system_execution_context* cctx) {
	example::fps::ApplyDrag::context ctx{cctx};
	example::fps::ApplyDrag::impl(ctx);
}
void example__fps__ResumeStreaming (struct ecsact_system_execution_context* cctx) {
	example::fps::ResumeStreaming::context ctx{cctx};
	example::fps::ResumeStreaming::impl(ctx);
}
void example__fps__TogglePushedEntities (struct ecsact_system_execution_context* cctx) {
	example::fps::TogglePushedEntities::context ctx{cctx};
	example::fps::TogglePushedEntities::impl(ctx);
}
void example__fps__RemovePushing (struct ecsact_system_execution_context* cctx) {
	example::fps::RemovePushing::context ctx{cctx};
	example::fps::RemovePushing::impl(ctx);
}
void example__fps__StunnedExpiry (struct ecsact_system_execution_context* cctx) {
	example::fps::StunnedExpiry::context ctx{cctx};
	example::fps::StunnedExpiry::impl(ctx);
}
void example__fps__StartPush (struct ecsact_system_execution_context* cctx) {
	example::fps::StartPush::context ctx{cctx};
	example::fps::StartPush::impl(ctx);
}
void example__fps__FinishPush (struct ecsact_system_execution_context* cctx) {
	example::fps::FinishPush::context ctx{cctx};
	example::fps::FinishPush::impl(ctx);
}
void example__fps__Move (struct ecsact_system_execution_context* cctx) {
	example::fps::Move::context ctx{cctx};
	example::fps::Move::impl(ctx);
}
