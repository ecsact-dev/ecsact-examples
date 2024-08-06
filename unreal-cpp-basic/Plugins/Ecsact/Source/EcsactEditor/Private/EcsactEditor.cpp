#include "EcsactEditor.h"
#include "Containers/Ticker.h"
#include "Misc/Paths.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Editor.h"
#include "HAL/PlatformProcess.h"

#define LOCTEXT_NAMESPACE "FEcsactEditorModule"

DEFINE_LOG_CATEGORY(EcsactEditor);

using ThisClass = FEcsactEditorModule;

auto FEcsactEditorModule::SpawnEcsactCli(
	const TCHAR*    Args,
	FOnExitDelegate OnExit
) -> void {
	check(OnExit.IsBound());

	if(!GEditor || !GEditor->IsTimerManagerValid()) {
		UE_LOG(
			EcsactEditor,
			Error,
			TEXT("Cannot spawn Ecsact CLI before editor timer manager is available")
		);
		OnExit.Execute(-1, {});
		return;
	}

	auto proc_id = uint32{};

	void* write_pipe;
	void* read_pipe;
	FPlatformProcess::CreatePipe(read_pipe, write_pipe, true);

	auto proc_handle = FPlatformProcess::CreateProc( //
		TEXT("ecsact"),
		Args,
		false,
		true,
		false,
		&proc_id,
		0,
		nullptr,
		read_pipe,
		write_pipe
	);

	if(proc_handle.IsValid()) {
		auto timer_manager = GEditor->GetTimerManager();
		auto output = FString{};

		auto handle = FTimerHandle{};
		timer_manager->SetTimer(
			handle,
			[=, this, OnExit = std::move(OnExit)] {
				EcsactCliProcTimerHandle(
					proc_handle,
					timer_manager,
					read_pipe,
					write_pipe,
					output,
					std::move(OnExit)
				);
			},
			0.15f,
			false
		);
	} else {
		UE_LOG(EcsactEditor, Error, TEXT("Failed to create Ecsact CLI process"));
		OnExit.Execute(1, FString{});
	}
}

auto FEcsactEditorModule::EcsactCliProcTimerHandle(
	FProcHandle                     ProcHandle,
	TSharedRef<class FTimerManager> TimerManager,
	void*                           PipeRead,
	void*                           PipeWrite,
	FString                         Output,
	FOnExitDelegate                 OnExit
) -> void {
	auto handle = FTimerHandle{};

	Output += FPlatformProcess::ReadPipe(PipeRead);

	if(!FPlatformProcess::IsProcRunning(ProcHandle)) {
		auto exit_code = int32{};
		if(FPlatformProcess::GetProcReturnCode(ProcHandle, &exit_code)) {
			FPlatformProcess::ClosePipe(PipeRead, PipeWrite);
			FPlatformProcess::TerminateProc(ProcHandle);
			OnExit.Execute(exit_code, Output);
		} else {
			UE_LOG(
				EcsactEditor,
				Error,
				TEXT("Failed to get exit code when spawning Ecsact CLI")
			);
			OnExit.Execute(-1, Output);
		}
		return;
	}

	TimerManager->SetTimer(
		handle,
		[=, this, OnExit = std::move(OnExit)] {
			EcsactCliProcTimerHandle(
				ProcHandle,
				TimerManager,
				PipeRead,
				PipeWrite,
				Output,
				std::move(OnExit)
			);
		},
		0.15f,
		false
	);
}

auto FEcsactEditorModule::StartupModule() -> void {
	UE_LOG(EcsactEditor, Warning, TEXT("Ecsact Editor Module StartupModule()"));
	FEditorDelegates::OnEditorInitialized.AddRaw(
		this,
		&ThisClass::OnEditorInitialized
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
		FOnExitDelegate::CreateLambda([](int32 exit_code, FString output) -> void {
			if(exit_code == 0) {
				UE_LOG(EcsactEditor, Warning, TEXT("Ecsact Version: %s"), *output);
			} else {
				UE_LOG(
					EcsactEditor,
					Error,
					TEXT("Ecsact CLI exited with code %i while trying to get version"),
					exit_code
				);
			}
		})
	);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEcsactEditorModule, EcsactEditor)
