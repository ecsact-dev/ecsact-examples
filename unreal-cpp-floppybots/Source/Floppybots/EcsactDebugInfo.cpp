#include "EcsactDebugInfo.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"

auto UEcsactDebugInfo::GetAsyncTick(const UObject* WorldContext) -> int {
	auto runner = EcsactUnrealExecution::RunnerOrWarn(WorldContext->GetWorld()).Get();
	if(!runner) {
		return 0;
	}

	auto async_runner = Cast<UEcsactAsyncRunner>(runner);
	if(!async_runner) {
		return 0;
	}

	return async_runner->GetAsyncSessionTick();
}
