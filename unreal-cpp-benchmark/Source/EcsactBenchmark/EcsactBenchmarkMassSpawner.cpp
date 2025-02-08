
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
#include "ecsact/si/wasm.h"
#include <filesystem>

UEcsactBenchmarkMassSpawner::UEcsactBenchmarkMassSpawner() {}

auto UEcsactBenchmarkMassSpawner::CreateEcsactEntities(int count) -> void {

  registry.emplace("Benchmark");
  evc.emplace();

  evc->set_init_callback<benchmark::Counter>(
      [this](auto entity_id, const auto comp) {
        this->InitCounter(entity_id, comp);
      });

  evc->set_update_callback<benchmark::Counter>(
      [this](auto entity_id, const auto comp) {
        this->UpdateCounter(entity_id, comp);
      });

  auto exec_options = ecsact::core::execution_options{};

  for (int i = 0; i < count; ++i) {
    auto entity = registry->create_entity();

    auto benchmark_counter = benchmark::Counter{.value = 0};

    exec_options.add_component(entity, &benchmark_counter);
  }
  auto exec_err = registry->execute_systems(std::array{exec_options}, *evc);
  if (exec_err != ECSACT_EXEC_SYS_OK) {
    UE_LOG(LogTemp, Error, TEXT("Ecsact system execution failed"));
  } else {
    UE_LOG(LogTemp, Log, TEXT("ECSACT: Created %i entities"), count);
  }
}

auto UEcsactBenchmarkMassSpawner::CreateMassEntities(int count) -> void {
  auto *world = GetWorld();
  check(world);

  const auto &entity_template = config->GetOrCreateEntityTemplate(*world);
  auto new_entity_handles = TArray<FMassEntityHandle>{};

  auto mass_spawner = world->GetSubsystem<UMassSpawnerSubsystem>();

  for (int i = 0; i < count; ++i) {
    mass_spawner->SpawnEntities(entity_template, 1, new_entity_handles);
    mass_entities.Add(new_entity_handles[0]);
  }
  UE_LOG(LogTemp, Log, TEXT("MASS: Created %i entities"), count);
}

auto UEcsactBenchmarkMassSpawner::LoadWASMFiles() -> void {
  auto cwd = FString{std::filesystem::current_path().string().c_str()};

  UE_LOG(LogTemp, Log, TEXT("CWD %s"), *cwd);
  auto file_path =
      FString{"C:/Users/Austin/Documents/programming/ecsact/ecsact-examples/"
              "unreal-cpp-benchmark/Binaries/SystemImpls.wasm"};

  auto err = ecsact_si_wasm_load_file(
      const_cast<char *>(TCHAR_TO_UTF8(*file_path)),
      EcsactUnreal::CodegenMeta::BenchmarkSystemLikeIds.size(),
      const_cast<ecsact_system_like_id *>(
          EcsactUnreal::CodegenMeta::BenchmarkSystemLikeIds.data()),
      const_cast<const char **>(
          EcsactUnreal::CodegenMeta::BenchmarkExportNames.data()));

  if (err != ECSACT_SI_WASM_OK) {
#define HANDLE_ECSACT_SI_ERROR_CASE(err)                                       \
  case err:                                                                    \
    UE_LOG(LogTemp, Error, TEXT("ecsact_si_wasm_load_file error: " #err));     \
    break
    switch (err) {
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

auto UEcsactBenchmarkMassSpawner::InitCounter( //
    ecsact_entity_id Entity, const benchmark::Counter &) -> void {

  UE_LOG(LogTemp, Log, TEXT("Counter started on entity %i"), Entity);
}

auto UEcsactBenchmarkMassSpawner::UpdateCounter( //
    ecsact_entity_id Entity, const benchmark::Counter &counter) -> void {

  UE_LOG(LogTemp, Log, TEXT("Counter update on entity %i to %i"), Entity,
         counter.value);
}

auto UEcsactBenchmarkMassSpawner::ExecuteSystems(int count) -> void {
  for (int i = 0; i < count; ++i) {
    registry->execute_systems(1, *evc);
  }
}

void UEcsactBenchmarkMassSpawner::StartMassSpawner( //
    UObject *WorldContext, EcsactBenchmarkType BenchmarkType) {
  UE_LOG(LogTemp, Warning, TEXT("BENCHMARKTYPE: %s"),
         *UEnum::GetValueAsString(BenchmarkType));

  auto *world = WorldContext->GetWorld();
  check(world);

  auto ecsact_game_subsystem =
      world->GetGameInstance()->GetSubsystem<UEcsactGameInstanceSubsystem>();
  check(ecsact_game_subsystem);

  ecsact_game_subsystem->StartCustomRunner<UEcsactBenchmarkRunner>();
  auto runner = EcsactUnrealExecution::Runner(world);

  if (!runner.IsValid()) {
    UE_LOG(LogTemp, Error, TEXT("Provided runner is invalid"));
    return;
  }

  auto mass_spawner_subsystem =
      runner->GetSubsystem<UEcsactBenchmarkMassSpawner>();

  if (mass_spawner_subsystem) {
    mass_spawner_subsystem->OnStartButtonPressed(BenchmarkType);
  } else {
    UE_LOG(LogTemp, Error, TEXT("BenchmarkMassSpawner can't be found"));
  }
}
