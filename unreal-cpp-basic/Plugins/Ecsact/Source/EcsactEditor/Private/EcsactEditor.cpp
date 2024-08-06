#include "EcsactEditor.h"
#include "Async/TaskGraphInterfaces.h"
#include "Containers/Ticker.h"
#include "Misc/Paths.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Editor.h"
#include "HAL/PlatformProcess.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "EcsactSettings.h"

#define LOCTEXT_NAMESPACE "FEcsactEditorModule"

DEFINE_LOG_CATEGORY(EcsactEditor);

auto FEcsactEditorModule::SpawnEcsactCli(
	const FString&  Args,
	FOnExitDelegate OnExit
) -> void {
	check(OnExit.IsBound());

	AsyncTask(
		ENamedThreads::BackgroundThreadPriority,
		[=, OnExit = std::move(OnExit)] {
			auto exit_code = int32{};
			auto std_out = FString{};
			auto std_err = FString{};
			FPlatformProcess::ExecProcess(
				TEXT("ecsact"),
				*Args,
				&exit_code,
				&std_out,
				&std_err,
				nullptr,
				true
			);

			AsyncTask(ENamedThreads::GameThread, [=, OnExit = std::move(OnExit)] {
				OnExit.Execute(exit_code, std_out, std_err);
			});
		}
	);
}

auto FEcsactEditorModule::StartupModule() -> void {
	auto& settings_module =
		FModuleManager::GetModuleChecked<ISettingsModule>("Settings");
	auto settings_container = settings_module.GetContainer("Project");
	auto settings_section = settings_module.RegisterSettings(
		"Project",
		"Plugins",
		"Ecsact",
		LOCTEXT("EcsactSettingsName", "Ecsact"),
		LOCTEXT("EcsactSettingsDescription", "Configuration settings for Ecsact"),
		GetMutableDefault<UEcsactSettings>()
	);
	check(settings_section.IsValid());
	settings_section->OnModified().BindRaw(
		this,
		&FEcsactEditorModule::OnEcsactSettingsModified
	);

	FEditorDelegates::OnEditorInitialized.AddRaw(
		this,
		&FEcsactEditorModule::OnEditorInitialized
	);
}

auto FEcsactEditorModule::ShutdownModule() -> void {
	UE_LOG(EcsactEditor, Warning, TEXT("Ecsact Editor Module ShutdownModule()"));
	FEditorDelegates::OnEditorInitialized.RemoveAll(this);
}

auto FEcsactEditorModule::PreUnloadCallback() -> void {
	UE_LOG(
		EcsactEditor,
		Warning,
		TEXT("Ecsact Editor Module PreUnloadCallback()")
	);
}

auto FEcsactEditorModule::PostLoadCallback() -> void {
	UE_LOG(
		EcsactEditor,
		Warning,
		TEXT("Ecsact Editor Module PostLoadCallback()")
	);
}

auto FEcsactEditorModule::SupportsDynamicReloading() -> bool {
	return true;
}

auto FEcsactEditorModule::OnEditorInitialized(double Duration) -> void {
	SpawnEcsactCli(
		TEXT("--version"),
		FOnExitDelegate::CreateLambda(
			[](int32 ExitCode, FString StdOut, FString StdErr) -> void {
				if(ExitCode == 0) {
					UE_LOG(EcsactEditor, Warning, TEXT("Ecsact Version: %s"), *StdOut);
				} else {
					UE_LOG(
						EcsactEditor,
						Error,
						TEXT("Ecsact CLI exited with code %i while trying to get version: "
								 "%s"),
						ExitCode,
						*StdErr
					);
				}
			}
		)
	);
}

auto FEcsactEditorModule::OnEcsactSettingsModified() -> bool {
	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEcsactEditorModule, EcsactEditor)
