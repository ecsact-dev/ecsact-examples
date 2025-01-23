// GENERATED FILE - DO NOT EDIT
#ifndef EXAMPLE__FPS_H
#define EXAMPLE__FPS_H

#include "ecsact/runtime/common.h"


ECSACT_EXTERN
ECSACT_EXPORT("example__fps__StartPush")
void example__fps__StartPush(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__FinishPush")
void example__fps__FinishPush(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__Move")
void example__fps__Move(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__StunTimer")
void example__fps__StunTimer(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__PusherExpireChecker")
void example__fps__PusherExpireChecker(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__PusherApplyExpired")
void example__fps__PusherApplyExpired(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__FinishPush__PushEntities")
void example__fps__FinishPush__PushEntities(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__RemovePushCharge")
void example__fps__RemovePushCharge(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__TickPushCharge")
void example__fps__TickPushCharge(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__ApplyPush")
void example__fps__ApplyPush(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__ApplyVelocity")
void example__fps__ApplyVelocity(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__ApplyDrag")
void example__fps__ApplyDrag(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__ResumeStreaming")
void example__fps__ResumeStreaming(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__TogglePushedEntities")
void example__fps__TogglePushedEntities(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__RemovePushing")
void example__fps__RemovePushing(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("example__fps__StunnedExpiry")
void example__fps__StunnedExpiry(struct ecsact_system_execution_context*);

#endif // EXAMPLE__FPS_H
