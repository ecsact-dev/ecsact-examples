// Copyright Epic Games, Inc. All Rights Reserved.

#include "EcsactUnrealFpsCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnrealFpsProjectile.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnrealFps.ecsact.hh"

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
	FirstPersonCameraComponent->SetRelativeLocation( // position the camera
		FVector(-10.f, 0.f, 60.f)
	);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st
	// person' view (when controlling this pawn)
	Mesh1P =
		CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	// Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AEcsactUnrealFpsCharacter::BeginPlay() {
	Super::BeginPlay();
}

void AEcsactUnrealFpsCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	if(CharacterEntity != ECSACT_INVALID_ID(entity)) {
		auto runner = EcsactUnrealExecution::Runner().Get();
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

	// Jumping
	eic->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	eic->BindAction(
		JumpAction,
		ETriggerEvent::Completed,
		this,
		&ACharacter::StopJumping
	);

	// Moving
	eic->BindAction(
		MoveAction,
		ETriggerEvent::Triggered,
		this,
		&AEcsactUnrealFpsCharacter::Move
	);

	// Looking
	eic->BindAction(
		LookAction,
		ETriggerEvent::Triggered,
		this,
		&AEcsactUnrealFpsCharacter::Look
	);
}

void AEcsactUnrealFpsCharacter::Move(const FInputActionValue& Value) {
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller != nullptr) {
		// add movement
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AEcsactUnrealFpsCharacter::Look(const FInputActionValue& Value) {
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if(Controller != nullptr) {
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
