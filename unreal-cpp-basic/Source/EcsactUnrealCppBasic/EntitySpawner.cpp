#include "EntitySpawner.h"
#include "ecsact/runtime/core.hh"
#include "Example.ecsact.hh"

AEntitySpawner::AEntitySpawner() {
	PrimaryActorTick.bCanEverTick = true;
}

void AEntitySpawner::BeginPlay() {
	Super::BeginPlay();
}

void AEntitySpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
