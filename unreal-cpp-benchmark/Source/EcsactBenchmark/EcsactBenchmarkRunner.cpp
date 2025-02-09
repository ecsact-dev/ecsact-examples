#include "EcsactBenchmarkRunner.h"
#include "ecsact/runtime/core.h"
#include "ecsact/runtime/core.hh"

auto UEcsactBenchmarkRunner::Start() -> void {
	Super::Start();
	should_run = true;
	registry.emplace("Benchmark");
}

auto UEcsactBenchmarkRunner::Stop() -> void {
	Super::Stop();
	should_run = false;
}

auto UEcsactBenchmarkRunner::Tick(float deltaTime) -> void {
	Super::Tick(deltaTime);
	if(ecsact_execute_systems && should_run) {
		ecsact_execution_options* exec_opts = nullptr;
		if(ExecutionOptions != nullptr && ExecutionOptions->IsNotEmpty()) {
			exec_opts = ExecutionOptions->GetCPtr();
		}
		auto err = ecsact_execute_systems( //
			registry->id(),
			1,
			exec_opts,
			GetEventsCollector()
		);
		if(ExecutionOptions != nullptr) {
			ExecutionOptions->Clear();
		}
	}
}
