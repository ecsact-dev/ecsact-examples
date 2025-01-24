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
#include "EcsactUnrealExampleMovementComponent.h"
#include "MassCommonFragments.h"

//////////////////////////////////////////////////////////////////////////
// AEcsactUnrealFpsCharacter

AEcsactUnrealFpsCharacter::AEcsactUnrealFpsCharacter() {
	RootCollision =
		CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Collision"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootCollision);

	MovementComponent =
		CreateDefaultSubobject<UEcsactUnrealExampleMovementComponent>( //
			TEXT("Movement")
		);
	MovementComponent->SetUpdatedComponent(RootCollision);
	MovementComponent->UpdatedComponent = RootCollision;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootCollision);
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetUsingAbsoluteRotation(true);
	CameraComponent->SetUsingAbsoluteLocation(true);

	PushDetectionSphere =
		CreateDefaultSubobject<USphereComponent>(TEXT("Push Detection Sphere"));
	PushDetectionSphere->InitSphereRadius(300.f);
	PushDetectionSphere->SetupAttachment(RootComponent);
	PushDetectionSphere->SetCollisionProfileName("OverlapAllDynamic");
	PushDetectionSphere->SetCollisionEnabled(ECollisionEnabled::ProbeOnly);
}

void AEcsactUnrealFpsCharacter::BeginPlay() {
	Super::BeginPlay();
}

auto AEcsactUnrealFpsCharacter::SetMoveDirection(float X, float Y) -> void {
	MovementComponent->SetMoveDirection(X, Y);
}

bool AEcsactUnrealFpsCharacter::IsMoveInputIgnored() const {
	return false;
}

void AEcsactUnrealFpsCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	CameraComponent->SetWorldLocationAndRotationNoPhysics(
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

auto AEcsactUnrealFpsCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent
) -> void {
	auto* eic = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	check(eic);

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
		&AEcsactUnrealFpsCharacter::StartPush
	);
	eic->BindAction(
		PushAction,
		ETriggerEvent::Completed,
		this,
		&AEcsactUnrealFpsCharacter::FinishPush
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
		if(!MovementComponent->IsMoveDirectionSimilar(move.x, move.y)) {
			runner->PushAction(move);
			// If we're being locally controlled we can should set the move direction
			// immediately.
			if(Controller) {
				SetMoveDirection(move.x, move.y);
			}
		}
	}
}

void AEcsactUnrealFpsCharacter::StartPush(const FInputActionValue& Value) {
	auto runner = EcsactUnrealExecution::Runner(GetWorld()).Get();
	if(!runner) {
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Start push action"));
	auto StartPushAction = example::fps::StartPush{
		.player_id = CharacterPlayerId,
	};

	runner->PushAction(StartPushAction);
}

void AEcsactUnrealFpsCharacter::FinishPush(const FInputActionValue& Value) {
	auto runner = EcsactUnrealExecution::Runner(GetWorld()).Get();
	if(!runner) {
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Finish push action"));
	auto FinishPushAction = example::fps::FinishPush{
		.player_id = CharacterPlayerId,
	};
	runner->PushAction(FinishPushAction);

	// auto MassSpawner = runner->GetSubsystem<UEcsactEntityMassSpawner>();
	// MassSpawner->Push(CharacterPlayerId);
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

auto AEcsactUnrealFpsCharacter::GetPlayerColour(int player_id) -> FLinearColor {
	constexpr auto golden_ratio = 0.618033988749895f;

	auto hue = std::fmod<float>( //
		static_cast<float>(player_id) * golden_ratio,
		1.0f
	);

	auto s = 0.8f; // Saturation
	auto v = 0.9f; // Value

	auto h_i = static_cast<int>(hue * 6);
	auto f = hue * 6 - h_i;
	auto p = v * (1 - s);
	auto q = v * (1 - f * s);
	auto t = v * (1 - (1 - f) * s);

	switch(h_i) {
		case 0:
			return FLinearColor{v, t, p};
		case 1:
			return FLinearColor{q, v, p};
		case 2:
			return FLinearColor{p, v, t};
		case 3:
			return FLinearColor{p, q, v};
		case 4:
			return FLinearColor{t, p, v};
		default:
			return FLinearColor{v, p, q};
	}
}
