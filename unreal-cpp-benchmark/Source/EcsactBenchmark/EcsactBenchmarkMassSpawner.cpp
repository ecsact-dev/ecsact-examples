
#include "EcsactBenchmarkMassSpawner.h"
#include "EcsactBenchmark/EcsactBenchmark.ecsact.hh"
#include "EcsactBenchmark/EcsactBenchmark__ecsact__ue.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "ecsact/si/wasm.h"
#include <filesystem>

auto UEcsactBenchmarkMassSpawner::CreateMassEntities(int count, bool UseEcsact)
    -> void {
  auto runner = GetRunner();

  for (int i = 0; i < count; ++i) {
    if (UseEcsact) {
      runner->CreateEntity()
          .AddComponent(benchmark::Counter{.value = 0})
          .OnCreate(TDelegate<void(ecsact_entity_id)>::CreateLambda( //
              [](auto entity) {
                UE_LOG(LogTemp, Warning, TEXT("Ecsact entity %i created"),
                       static_cast<int>(entity));
              }));
    } else {
      runner->CreateEntity()
          .AddComponent(benchmark::Counter{.value = 0})
          .AddComponent(benchmark::MassOnly{})
          .OnCreate(TDelegate<void(ecsact_entity_id)>::CreateLambda( //
              [](auto entity) {
                UE_LOG(LogTemp, Warning, TEXT("Mass entity %i created"),
                       static_cast<int>(entity));
              }));
    }
  }
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
  } else {

    UE_LOG(LogTemp, Log, TEXT("yay"));
  }
}

auto UEcsactBenchmarkMassSpawner::InitCounter_Implementation(
    int32 Entity, FBenchmarkCounter Counter) -> void {
  Super::InitCounter_Implementation(Entity, Counter);

  UE_LOG(LogTemp, Log, TEXT("Counter started on entity %i"), Entity);
}

auto UEcsactBenchmarkMassSpawner::UpdateCounter_Implementation(
    int32 Entity, FBenchmarkCounter Counter) -> void {
  Super::UpdateCounter_Implementation(Entity, Counter);

  UE_LOG(LogTemp, Log, TEXT("Counter updated on entity %i to %i"), Entity,
         Counter.Value);
}
