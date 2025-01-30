#include "ExampleCustomEcsactRunnerStarter.h"
#include "ecsact/runtime/core.h"
#include "ecsact/wasm.h"
#include "Ecsact/Private/EcsactGameInstanceSubsystem.h"
#include "Engine/GameInstance.h"
#include "EcsactUnreal/EcsactSyncRunner.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactNetUnreal/Wasm/EcsactNetWasmSettings.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactEntityMassSpawner.h"

static auto LoadWasmSystemImpls() -> void {
	// TODO: move this out of ecsact net and into ecsact plugin
	const auto* settings = GetDefault<UEcsactNetWasmSettings>();
	for(auto wasm_file : settings->SystemImplWasmFiles) {
		auto file_path = wasm_file.FilePath;
		if(FPaths::IsRelative(wasm_file.FilePath)) {
			file_path = FPaths::Combine(FPaths::ProjectDir(), file_path);
		}

		if(ecsactsi_wasm_load_file != nullptr) {
			// reason for const_casts:
			// https://github.com/ecsact-dev/ecsact_si_wasm/issues/80
			auto err = ecsactsi_wasm_load_file(
				const_cast<char*>(TCHAR_TO_UTF8(*file_path)),
				EcsactUnreal::CodegenMeta::ExampleFpsSystemLikeIds.size(),
				const_cast<ecsact_system_like_id*>(
					EcsactUnreal::CodegenMeta::ExampleFpsSystemLikeIds.data()
				),
				const_cast<const char**>(
					EcsactUnreal::CodegenMeta::ExampleFpsExportNames.data()
				)
			);
			if(err != ECSACTSI_WASM_OK) {
#define HANDLE_ECSACTSI_ERROR_CASE(err)                                   \
	case err:                                                               \
		UE_LOG(LogTemp, Error, TEXT("ecsactsi_wasm_load_file error: " #err)); \
		break
				switch(err) {
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_FILE_OPEN_FAIL);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_FILE_READ_FAIL);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_COMPILE_FAIL);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_INSTANTIATE_FAIL);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_EXPORT_NOT_FOUND);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_EXPORT_INVALID);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_GUEST_IMPORT_UNKNOWN);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_GUEST_IMPORT_INVALID);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_INITIALIZE_FAIL);
					HANDLE_ECSACTSI_ERROR_CASE(ECSACTSI_WASM_ERR_NO_SET_SYSTEM_EXECUTION);
					case ECSACTSI_WASM_OK:
						break;
				}
#undef HANDLE_ECSACTSI_ERROR_CASE
			}
		} else {
			UE_LOG(
				LogTemp,
				Error,
				TEXT("ecsactsi_wasm_load_file unavailable - cannot load wasm system "
						 "impls")
			);
		}
	}
}

auto UExampleCustomEcsactRunnerStarter::StartSingleplayerRunner( //
	UObject* WorldContext
) -> void {
	auto world = WorldContext->GetWorld();
	check(world);
	auto ecsact_game_subsystem =
		world->GetGameInstance()->GetSubsystem<UEcsactGameInstanceSubsystem>();
	check(ecsact_game_subsystem);

	LoadWasmSystemImpls();
	ecsact_game_subsystem->StartCustomRunner<UEcsactSyncRunner>();
	UEcsactEntityMassSpawner::SetStreamEntities(WorldContext, true);
}

auto UExampleCustomEcsactRunnerStarter::StartMultiplayerRunner( //
	UObject* WorldContext
) -> void {
	auto world = WorldContext->GetWorld();
	check(world);
	auto ecsact_game_subsystem =
		world->GetGameInstance()->GetSubsystem<UEcsactGameInstanceSubsystem>();
	check(ecsact_game_subsystem);
	ecsact_game_subsystem->StartCustomRunner<UEcsactAsyncRunner>();
}

auto UExampleCustomEcsactRunnerStarter::IsSingleplayerRunner( //
	UObject* WorldContext
) -> bool {
	auto world = WorldContext->GetWorld();
	check(world);
	auto runner = EcsactUnrealExecution::Runner(world).Get();
	return Cast<UEcsactAsyncRunner>(runner) == nullptr;
}
