// Copyright Epic Games, Inc. All Rights Reserved.

#include "EcsactUnrealFpsCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactEntityMassSpawner.h"
#include "MassCommonFragments.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AEcsactUnrealFpsCharacter

AEcsactUnrealFpsCharacter::AEcsactUnrealFpsCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent
	FirstPersonCameraComponent =
		CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = false;
	FirstPersonCameraComponent->SetUsingAbsoluteRotation(true);
	FirstPersonCameraComponent->SetUsingAbsoluteLocation(true);

	PushDetectionSphere =
		CreateDefaultSubobject<USphereComponent>(TEXT("Push Detection Sphere"));
	PushDetectionSphere->InitSphereRadius(300.f);
	PushDetectionSphere->SetupAttachment(RootComponent);
	PushDetectionSphere->SetCollisionProfileName("OverlapAllDynamic");
}

void AEcsactUnrealFpsCharacter::BeginPlay() {
	Super::BeginPlay();
}

auto AEcsactUnrealFpsCharacter::SetMoveDirection(float X, float Y) -> void {
	MoveDirX = X;
	MoveDirY = Y;
}

bool AEcsactUnrealFpsCharacter::IsMoveInputIgnored() const {
	return false;
}

void AEcsactUnrealFpsCharacter::Tick(float DeltaSeconds) {
	AddMovementInput(FVector::ForwardVector, MoveDirY);
	AddMovementInput(FVector::RightVector, MoveDirX);

	if(MoveDirX != 0.0f || MoveDirY != 0.0f) {
		auto move_vector = FVector{
			MoveDirX,
			-MoveDirY,
			GetActorLocation().Z,
		};

		auto new_rotation = move_vector.ToOrientationRotator();
		new_rotation.Pitch = 0.f;
		SetActorRotation(new_rotation);
	}

	Super::Tick(DeltaSeconds);

	FirstPersonCameraComponent->SetWorldLocationAndRotationNoPhysics(
		GetActorLocation() + CameraOffset,
		CameraRotation
	);

	if(CharacterEntity != ECSACT_INVALID_ID(entity)) {
		auto runner = EcsactUnrealExecution::Runner(GetWorld()).Get();
		auto actor_pos = GetActorLocation();
		auto actor_rot = GetActorRotation();
		runner->Stream(
			CharacterEntity,
			example::fps::Rotation{
				.pitch = static_cast<float>(actor_rot.Pitch),
				.yaw = static_cast<float>(actor_rot.Yaw),
				.roll = static_cast<float>(actor_rot.Roll),
			}
		);
		runner->Stream(
			CharacterEntity,
			example::fps::Position{
				.x = static_cast<float>(actor_pos.X),
				.y = static_cast<float>(actor_pos.Y),
				.z = static_cast<float>(actor_pos.Z),
			}
		);
	}
}

////////////////////////////////////////////////////////////////////////////
/// Input

void AEcsactUnrealFpsCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent
) {
	auto* eic = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(!eic) {
		UE_LOG(
			LogTemplateCharacter,
			Error,
			TEXT("'%s' Failed to find an Enhanced Input Component! This template "
					 "is built to use the Enhanced Input system. If you intend to use "
					 "the legacy system, then you will need to update this C++ file."),
			*GetNameSafe(this)
		);
		return;
	}

	eic->BindAction(
		MoveAction,
		ETriggerEvent::Triggered,
		this,
		&AEcsactUnrealFpsCharacter::Move
	);

	eic->BindAction(
		PushAction,
		ETriggerEvent::Triggered,
		this,
		&AEcsactUnrealFpsCharacter::Push
	);
}

void AEcsactUnrealFpsCharacter::Move(const FInputActionValue& Value) {
	auto runner = EcsactUnrealExecution::Runner(GetWorld()).Get();

	// input is a Vector2D
	FVector2D movement_vector = Value.Get<FVector2D>();

	if(runner) {
		auto move = example::fps::Move{
			.player_id = CharacterPlayerId,
			.x = static_cast<float>(movement_vector.X),
			.y = static_cast<float>(movement_vector.Y),
		};

		// Don't send any unncessary actions
		if(move.x != MoveDirX || move.y != MoveDirY) {
			runner->PushAction(move);
		}

		// If we're being locally controlled we can should set the move direction
		// immediately.
		if(Controller) {
			SetMoveDirection(move.x, move.y);
		}
	}
}

void AEcsactUnrealFpsCharacter::Push(const FInputActionValue& Value) {
	auto runner = EcsactUnrealExecution::Runner(GetWorld()).Get();

	if(runner) {
		auto MassSpawner = runner->GetSubsystem<UEcsactEntityMassSpawner>();
		MassSpawner->Push(CharacterPlayerId);
	}
}

void AEcsactUnrealFpsCharacter::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor*              OtherActor,
	UPrimitiveComponent* OtherComp,
	int32                OtherBodyIndex,
	bool                 bFromSweep,
	const FHitResult&    SweepResult
) {
	if(!OtherActor || OtherActor == this) {
		return;
	}
}

void AEcsactUnrealFpsCharacter::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComp,
	AActor*              OtherActor,
	UPrimitiveComponent* OtherComp,
	int32                OtherBodyIndex
) {
}
