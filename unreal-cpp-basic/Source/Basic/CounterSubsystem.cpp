#include "CounterSubsystem.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "Basic/Basic.ecsact.hh"
#include "ecsact/runtime/dynamic.h"

static auto CounterSystemImpl(ecsact_system_execution_context* ctx) -> void {
	auto count = basic::Count{};
	ecsact_system_execution_context_get(
		ctx,
		ecsact_id_cast<ecsact_component_like_id>(basic::Count::id),
		&count,
		nullptr
	);

	count.value += 1;

	ecsact_system_execution_context_update(
		ctx,
		ecsact_id_cast<ecsact_component_like_id>(basic::Count::id),
		&count,
		nullptr
	);
}

auto UCounterSubsystem::GetCounterTotal(UObject* WorldContext) -> int32 {
	auto world = WorldContext->GetWorld();
	check(world);
	auto runner = EcsactUnrealExecution::Runner(world).Get();
	check(runner);
	auto self = runner->GetSubsystem<ThisClass>();
	check(self);
	auto count_total = 0;
	for(auto&& [_, count] : self->AllCounts) {
		count_total += count;
	}
	return count_total;
}

auto UCounterSubsystem::RunnerStart_Implementation(UEcsactRunner* Runner) -> void {
	Super::RunnerStart_Implementation(Runner);
	if(ecsact_set_system_execution_impl == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("ecsact_set_system_execution_impl is unavailable in your Ecsact Runtime - please make sure your Ecsact Runtime is built"));
		return;
	}
	auto success = ecsact_set_system_execution_impl(
		ecsact_id_cast<ecsact_system_like_id>(basic::Counter::id),
		&CounterSystemImpl
	);

	if(!success) {
		UE_LOG(LogTemp, Error, TEXT("Failed to set Ecsact system implementation"));
	}

	Runner->CreateEntity()
		.AddComponent(basic::Count{});
}

auto UCounterSubsystem::InitCount_Implementation(int32 Entity, FBasicCount Count) -> void {
	Super::InitCount_Implementation(Entity, Count);
	AllCounts.Add(Entity) = 0;
}

auto UCounterSubsystem::UpdateCount_Implementation(int32 Entity, FBasicCount Count) -> void {
	Super::UpdateCount_Implementation(Entity, Count);
	*AllCounts.Find(Entity) = Count.Value;
}

auto UCounterSubsystem::RemoveCount_Implementation(int32 Entity, FBasicCount Count) -> void {
	Super::RemoveCount_Implementation(Entity, Count);
	AllCounts.Remove(Entity);
}
