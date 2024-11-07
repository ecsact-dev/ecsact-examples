#include "EcsactUnrealFpsProjectile.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AEcsactUnrealFpsProjectile::AEcsactUnrealFpsProjectile() {
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(
		this,
		&AEcsactUnrealFpsProjectile::OnHit
	); // set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(
		FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f)
	);
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp")
		);
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AEcsactUnrealFpsProjectile::OnHit(
	UPrimitiveComponent* HitComp,
	AActor*              OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector              NormalImpulse,
	const FHitResult&    Hit
) {
	// Only add impulse and destroy projectile if we hit a physics
	if((OtherActor != nullptr) && (OtherActor != this) &&
		 (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics()) {
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

auto AEcsactUnrealFpsProjectile::BeginDestroy() -> void {
	if(Entity != ECSACT_INVALID_ID(entity)) {
		auto runner = EcsactUnrealExecution::Runner();
		if(runner.IsValid()) {
			UE_LOG(LogTemp, Error, TEXT("Destroying projectile entity"));
			runner.Get()->DestroyEntity(Entity);
		} else {
			UE_LOG(LogTemp, Error, TEXT("Cannot destroy. Runner invalid."));
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Cannot destroy. Entity invalid"));
	}

	Super::BeginDestroy();
}
