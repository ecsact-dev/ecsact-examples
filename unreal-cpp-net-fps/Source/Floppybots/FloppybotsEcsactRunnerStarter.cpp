#include "FloppybotsEcsactRunnerStarter.h"
#include "ecsact/runtime/core.h"
#include "ecsact/si/wasm.h"
#include "Ecsact/Private/EcsactGameInstanceSubsystem.h"
#include "Engine/GameInstance.h"
#include "EcsactUnreal/EcsactSyncRunner.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactNetUnreal/Wasm/EcsactNetWasmSettings.h"
#include "Floppybots__ecsact__ue.h"
#include "EcsactEntityMassSpawner.h"

// static auto LoadWasmSystemImpls() -> void {
// 	// TODO: move this out of ecsact net and into ecsact plugin
// 	const auto* settings = GetDefault<UEcsactNetWasmSettings>();
// 	for(auto wasm_file : settings->SystemImplWasmFiles) {
// 		auto file_path = wasm_file.FilePath;
// 		if(FPaths::IsRelative(wasm_file.FilePath)) {
// 			file_path = FPaths::Combine(FPaths::ProjectDir(), file_path);
// 		}
//
// 		if(ecsact_si_wasm_load_file != nullptr) {
// 			// reason for const_casts:
// 			// https://github.com/ecsact-dev/ecsact_si_wasm/issues/80
// 			auto err = ecsact_si_wasm_load_file(
// 				const_cast<char*>(TCHAR_TO_UTF8(*file_path)),
// 				EcsactUnreal::CodegenMeta::ExampleFpsSystemLikeIds.size(),
// 				const_cast<ecsact_system_like_id*>(
// 					EcsactUnreal::CodegenMeta::ExampleFpsSystemLikeIds.data()
// 				),
// 				const_cast<const char**>(
// 					EcsactUnreal::CodegenMeta::ExampleFpsExportNames.data()
// 				)
// 			);
// 			if(err != ECSACT_SI_WASM_OK) {
// #define HANDLE_ECSACT_SI_ERROR_CASE(err)                                   \
// 	case err:                                                                \
// 		UE_LOG(LogTemp, Error, TEXT("ecsact_si_wasm_load_file error: " #err)); \
// 		break
// 				switch(err) {
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_FILE_OPEN_FAIL);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_FILE_READ_FAIL);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_COMPILE_FAIL);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_INSTANTIATE_FAIL);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_EXPORT_NOT_FOUND);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_EXPORT_INVALID);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_GUEST_IMPORT_UNKNOWN);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_GUEST_IMPORT_INVALID);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_INITIALIZE_FAIL);
// 					HANDLE_ECSACT_SI_ERROR_CASE(ECSACT_SI_WASM_ERR_NO_SET_SYSTEM_EXECUTION
// 					);
// 					case ECSACT_SI_WASM_OK:
// 						break;
// 				}
// #undef HANDLE_ECSACT_SI_ERROR_CASE
// 			}
// 		} else {
// 			UE_LOG(
// 				LogTemp,
// 				Error,
// 				TEXT("ecsact_si_wasm_load_file unavailable - cannot load wasm system "
// 						 "impls")
// 			);
// 		}
// 	}
// }

auto UFloppybotsEcsactRunnerStarter::StartSingleplayerRunner( //
	UObject* WorldContext
) -> void {
	auto world = WorldContext->GetWorld();
	check(world);
	auto ecsact_game_subsystem =
		world->GetGameInstance()->GetSubsystem<UEcsactGameInstanceSubsystem>();
	check(ecsact_game_subsystem);

	// LoadWasmSystemImpls();
	ecsact_game_subsystem->StartCustomRunner<UEcsactSyncRunner>();
	UEcsactEntityMassSpawner::SetStreamEntities(WorldContext, true);
}

auto UFloppybotsEcsactRunnerStarter::StartMultiplayerRunner( //
	UObject* WorldContext
) -> void {
	auto world = WorldContext->GetWorld();
	check(world);
	auto ecsact_game_subsystem =
		world->GetGameInstance()->GetSubsystem<UEcsactGameInstanceSubsystem>();
	check(ecsact_game_subsystem);
	// LoadWasmSystemImpls();
	ecsact_game_subsystem->StartCustomRunner<UEcsactAsyncRunner>();
}

auto UFloppybotsEcsactRunnerStarter::IsSingleplayerRunner( //
	UObject* WorldContext
) -> bool {
	auto world = WorldContext->GetWorld();
	check(world);
	auto runner = EcsactUnrealExecution::Runner(world).Get();
	return Cast<UEcsactAsyncRunner>(runner) == nullptr;
}
