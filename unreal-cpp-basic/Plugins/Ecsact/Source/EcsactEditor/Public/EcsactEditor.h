#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(EcsactEditor, Log, All);

class FEcsactEditorModule : public IModuleInterface {
public:
	using FOnExitDelegate = TDelegate<void(int32, FString, FString)>;

private:
	auto OnEditorInitialized(double Duration) -> void;
	auto OnEcsactSettingsModified() -> bool;

public:
	auto SpawnEcsactCli( //
		const FString&  Args,
		FOnExitDelegate OnExit
	) -> void;
	auto StartupModule() -> void override;
	auto ShutdownModule() -> void override;
	auto PreUnloadCallback() -> void override;
	auto PostLoadCallback() -> void override;
	auto SupportsDynamicReloading() -> bool override;
};
