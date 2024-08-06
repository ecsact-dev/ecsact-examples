#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(EcsactEditor, Log, All);

class FEcsactEditorModule : public IModuleInterface {
public:
	using FOnExitDelegate = TDelegate<void(int32, FString)>;

private:
	auto EcsactCliProcTimerHandle(
		FProcHandle                     ProcHandle,
		TSharedRef<class FTimerManager> TimerManager,
		void*                           ReadPipe,
		void*                           WritePipe,
		FString                         Output,
		FOnExitDelegate                 OnExit
	) -> void;

	auto OnEditorInitialized(double Duration) -> void;

public:
	auto SpawnEcsactCli( //
		const TCHAR*    Args,
		FOnExitDelegate OnExit
	) -> void;
	auto StartupModule() -> void override;
	auto ShutdownModule() -> void override;
	auto PreUnloadCallback() -> void override;
	auto PostLoadCallback() -> void override;
	auto SupportsDynamicReloading() -> bool override;
};
