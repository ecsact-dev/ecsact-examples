#include "EcsactUnrealFpsConnect.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "EcsactUnrealFps.ecsact.hh"

void UEcsactUnrealFpsConnect::CreateInitialEntities() {
	auto runner = EcsactUnrealExecution::Runner();

	// NOTE: For demonstration purposes only we're creating an entity for the
	// player right away. In a real multiplayer game your players will likely not
	// have permission to just create entities at will. Instead they will already
	// be created for them and any entity creation at runtime would occur during a
	// generator system of backend function. Refer to your Ecsact async
	// implemtnation for details.
	runner->CreateEntity()
		.AddComponent(example::fps::Player{})
		.AddComponent(example::fps::Position{})
		.AddComponent(example::fps::Rotation{});
}

void UEcsactUnrealFpsConnect::UnrealFpsConnect(FString ConnectionString) {
	auto runner = EcsactUnrealExecution::Runner();

	// NOTE: This isn't how you'd usually connect to an async runner. Instead you
	// should have some kind of UI or bootup sequence for your users. For
	// demonstration purposes this is simple, but only works with the references
	// async implementation.
	auto async_runner = Cast<UEcsactAsyncRunner>(runner);
	if(async_runner != nullptr) {
		using FAsyncRequestDoneCallback =
			IEcsactAsyncRunnerEvents::FAsyncRequestDoneCallback;
		async_runner->Connect( //
			TCHAR_TO_UTF8(*ConnectionString),
			FAsyncRequestDoneCallback::CreateLambda([] { CreateInitialEntities(); })
		);
	} else {
		CreateInitialEntities();
	}
}
