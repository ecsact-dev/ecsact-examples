// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_WeaponComponent.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "EcsactUnrealFps/EcsactUnrealFpsPlayerController.h"
#include "EcsactUnrealFpsCharacter.h"
#include "EcsactUnrealFpsProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EcsactUnrealFps.ecsact.hh"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent() {
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UTP_WeaponComponent::StartFiring() {
	UE_LOG(LogTemp, Warning, TEXT("StartFiring()"));
	if(Character == nullptr || Character->GetController() == nullptr) {
		return;
	}
	if(Character->CharacterEntity == ECSACT_INVALID_ID(entity)) {
		return;
	}

	auto pc = Cast<AEcsactUnrealFpsPlayerController>(Character->GetController());
	if(!pc) {
		return;
	}

	auto runner = EcsactUnrealExecution::Runner().Get();

	runner->PushAction(example::fps::StartFiring{pc->PlayerId});
}

void UTP_WeaponComponent::StopFiring() {
	UE_LOG(LogTemp, Warning, TEXT("StopFiring()"));
	if(Character == nullptr || Character->GetController() == nullptr) {
		return;
	}
	if(Character->CharacterEntity == ECSACT_INVALID_ID(entity)) {
		return;
	}

	auto pc = Cast<AEcsactUnrealFpsPlayerController>(Character->GetController());
	if(!pc) {
		return;
	}

	auto runner = EcsactUnrealExecution::Runner().Get();
	runner->PushAction(example::fps::StopFiring{pc->PlayerId});
}

bool UTP_WeaponComponent::AttachWeapon(
	AEcsactUnrealFpsCharacter* TargetCharacter
) {
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if(Character == nullptr ||
		 Character->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>(
		 )) {
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(
		EAttachmentRule::SnapToTarget,
		true
	);
	AttachToComponent(
		Character->GetMesh1P(),
		AttachmentRules,
		FName(TEXT("GripPoint"))
	);

	// add the weapon as an instance component to the character
	Character->AddInstanceComponent(this);

	// Set up action bindings
	if(APlayerController* PlayerController =
			 Cast<APlayerController>(Character->GetController())) {
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem =
				 ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
					 PlayerController->GetLocalPlayer()
				 )) {
			// Set the priority of the mapping to 1, so that it overrides the Jump
			// action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if(UEnhancedInputComponent* EnhancedInputComponent =
				 Cast<UEnhancedInputComponent>(PlayerController->InputComponent)) {
			EnhancedInputComponent->BindAction(
				FireAction,
				ETriggerEvent::Started,
				this,
				&UTP_WeaponComponent::StartFiring
			);

			EnhancedInputComponent->BindAction(
				FireAction,
				ETriggerEvent::Completed,
				this,
				&UTP_WeaponComponent::StopFiring
			);
		}
	}

	return true;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if(Character == nullptr) {
		return;
	}

	if(APlayerController* PlayerController =
			 Cast<APlayerController>(Character->GetController())) {
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem =
				 ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
					 PlayerController->GetLocalPlayer()
				 )) {
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}
