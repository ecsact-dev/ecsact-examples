// GENERATED FILE - DO NOT EDIT
#ifndef FLOPPYBOTS_H
#define FLOPPYBOTS_H

#include "ecsact/runtime/common.h"


ECSACT_EXTERN
ECSACT_EXPORT("floppybots__StartPush")
void floppybots__StartPush(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__FinishPush")
void floppybots__FinishPush(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__Move")
void floppybots__Move(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__StunTimer")
void floppybots__StunTimer(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__PusherExpireChecker")
void floppybots__PusherExpireChecker(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__PusherApplyExpired")
void floppybots__PusherApplyExpired(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__FinishPush__PushEntities")
void floppybots__FinishPush__PushEntities(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__RemovePushCharge")
void floppybots__RemovePushCharge(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__TickPushCharge")
void floppybots__TickPushCharge(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__ApplyPush")
void floppybots__ApplyPush(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__ApplyVelocity")
void floppybots__ApplyVelocity(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__ApplyDrag")
void floppybots__ApplyDrag(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__ResumeStreaming")
void floppybots__ResumeStreaming(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__TogglePushedEntities")
void floppybots__TogglePushedEntities(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__RemovePushing")
void floppybots__RemovePushing(struct ecsact_system_execution_context*);

ECSACT_EXTERN
ECSACT_EXPORT("floppybots__StunnedExpiry")
void floppybots__StunnedExpiry(struct ecsact_system_execution_context*);

#endif // FLOPPYBOTS_H
