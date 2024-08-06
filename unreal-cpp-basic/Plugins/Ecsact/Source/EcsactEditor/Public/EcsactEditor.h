#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(EcsactEditor, Log, All);

class FEcsactEditorModule : public IModuleInterface {
	FDelegateHandle SourcesWatchHandle;

public:
	using FOnExitDelegate = TDelegate<void(int32, FString, FString)>;

private:
	auto OnEditorInitialized(double Duration) -> void;
	auto OnEcsactSettingsModified() -> bool;
	auto OnProjectSourcesChanged( //
		const TArray<struct FFileChangeData>& FileChanges
	) -> void;

public:
	auto SpawnEcsactCli( //
		const TArray<FString>& Args,
		FOnExitDelegate        OnExit
	) -> void;

	auto RunCodegen() -> void;
	auto RunBuild() -> void;

	auto StartupModule() -> void override;
	auto ShutdownModule() -> void override;
	auto PreUnloadCallback() -> void override;
	auto PostLoadCallback() -> void override;
	auto SupportsDynamicReloading() -> bool override;
};
