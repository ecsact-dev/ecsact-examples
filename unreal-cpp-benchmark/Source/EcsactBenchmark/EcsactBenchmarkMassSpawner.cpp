
#include "EcsactBenchmarkMassSpawner.h"
#include "Ecsact/Private/EcsactGameInstanceSubsystem.h"
#include "EcsactBenchmark/EcsactBenchmark.ecsact.hh"
#include "EcsactBenchmark/EcsactBenchmark__ecsact__ue.h"
#include "EcsactBenchmarkRunner.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnreal/EcsactUnrealExecutionOptions.h"
#include "Logging/LogVerbosity.h"
#include "MassEntitySubsystem.h"
#include "MassSpawnerSubsystem.h"
#include "Fragments/MassCounterFragments.h"
#include "ecsact/si/wasm.h"
#include <filesystem>

UEcsactBenchmarkMassSpawner::UEcsactBenchmarkMassSpawner() {
}

auto UEcsactBenchmarkMassSpawner::CreateEcsactEntities(int count) -> void {
	auto runner = GetRunner();
	check(runner);

	GetWorld()->GetTimerManager().SetTimer(
		RunTimer,
		[this]() {
			UE_LOG(LogTemp, Log, TEXT("Stop dat runner"));
			auto runner = GetRunner();
			runner->Stop();
		},
		5.0f,
		false
	);

	for(int i = 0; i < count; ++i) {
		runner->CreateEntity().AddComponent<benchmark::Counter>({.value = 0});
	}
	UE_LOG(LogTemp, Log, TEXT("ECSACT: Created %i entities"), count);
}

auto UEcsactBenchmarkMassSpawner::CreateMassEntities(int count) -> void {
	auto* world = GetWorld();
	check(world);

	const auto& entity_template = config->GetOrCreateEntityTemplate(*world);

	auto mass_spawner = world->GetSubsystem<UMassSpawnerSubsystem>();

	// GetWorld()->GetTimerManager().SetTimer(
	// 	RunTimer,
	// 	[this]() {
	// 		UE_LOG(LogTemp, Log, TEXT("Remove mass tag"));
	// 		auto& entity_manager = //
	// 			GetWorld()
	// 				->GetSubsystem<UMassEntitySubsystem>()
	// 				->GetMutableEntityManager();
	// 		for(auto entity_handle : mass_entities) {
	// 			entity_manager.Defer().RemoveTag<FRunMassCounter>(entity_handle);
	// 		}
	// 	},
	// 	5.0f,
	// 	false
	// );

	for(int i = 0; i < count; ++i) {
		auto new_entity_handles = TArray<FMassEntityHandle>{};
		mass_spawner->SpawnEntities(entity_template, 1, new_entity_handles);
		mass_entities.Add(new_entity_handles[0]);
	}
	UE_LOG(LogTemp, Log, TEXT("MASS: Created %i entities"), count);
}

auto UEcsactBenchmarkMassSpawner::LoadWASMFiles() -> void {
	auto cwd = FString{std::filesystem::current_path().string().c_str()};

	UE_LOG(LogTemp, Log, TEXT("CWD %s"), *cwd);
	auto file_path = FString{
		"C:/Users/Austin/Documents/programming/ecsact/ecsact-examples/"
		"unreal-cpp-benchmark/Binaries/SystemImpls.wasm"
	};

	auto err = ecsact_si_wasm_load_file(
		const_cast<char*>(TCHAR_TO_UTF8(*file_path)),
		EcsactUnreal::CodegenMeta::BenchmarkSystemLikeIds.size(),
		const_cast<ecsact_system_like_id*>(
			EcsactUnreal::CodegenMeta::BenchmarkSystemLikeIds.data()
		),
		const_cast<const char**>(
			EcsactUnreal::CodegenMeta::BenchmarkExportNames.data()
		)
	);

	if(err != ECSACT_SI_WASM_OK) {
#define HANDLE_ECSACT_SI_ERROR_CASE(err)                                   \
	case err:                                                                \
		UE_LOG(LogTemp, Error, TEXT("ecsact_si_wasm_load_file error: " #err)); \
		break
		switch(err) {
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_FILE_OPEN_FAIL);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_FILE_READ_FAIL);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_COMPILE_FAIL);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_INSTANTIATE_FAIL);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_EXPORT_NOT_FOUND);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_EXPORT_INVALID);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_GUEST_IMPORT_UNKNOWN);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_GUEST_IMPORT_INVALID);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_INITIALIZE_FAIL);
			HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_NO_SET_SYSTEM_EXECUTION);
			case ECSACT_SI_WASM_OK:
				break;
		}
#undef HANDLE_ECSACT_SI_ERROR_CASE
	}
}

void UEcsactBenchmarkMassSpawner::InitCounter_Implementation(
	int32 Entity,
	FBenchmarkCounter
) {
	// UE_LOG(LogTemp, Log, TEXT("Counter init on entity %i"), Entity);
}

void UEcsactBenchmarkMassSpawner::UpdateCounter_Implementation(
	int32             Entity,
	FBenchmarkCounter Counter
) {
	// UE_LOG(
	// 	LogTemp,
	// 	Log,
	// 	TEXT("Counter updated on entity %i to %i"),
	// 	Entity,
	// 	Counter.Value
	// );
}

void UEcsactBenchmarkMassSpawner::StartMassSpawner( //
	UObject*            WorldContext,
	EcsactBenchmarkType BenchmarkType
) {
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("BENCHMARKTYPE: %s"),
		*UEnum::GetValueAsString(BenchmarkType)
	);

	auto* world = WorldContext->GetWorld();
	check(world);

	auto ecsact_game_subsystem =
		world->GetGameInstance()->GetSubsystem<UEcsactGameInstanceSubsystem>();
	check(ecsact_game_subsystem);

	ecsact_game_subsystem->StartCustomRunner<UEcsactBenchmarkRunner>();
	auto runner = EcsactUnrealExecution::Runner(world);

	if(!runner.IsValid()) {
		UE_LOG(LogTemp, Error, TEXT("Provided runner is invalid"));
		return;
	}

	auto mass_spawner_subsystem =
		runner->GetSubsystem<UEcsactBenchmarkMassSpawner>();

	if(mass_spawner_subsystem) {
		mass_spawner_subsystem->OnStartButtonPressed(BenchmarkType);
	} else {
		UE_LOG(LogTemp, Error, TEXT("BenchmarkMassSpawner can't be found"));
	}
}
