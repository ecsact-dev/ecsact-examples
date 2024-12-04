// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ecsact/runtime/common.h"
#include "EcsactUnrealFpsCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)

class AEcsactUnrealFpsCharacter : public ACharacter {
	GENERATED_BODY()

	float MoveDirX;
	float MoveDirY;

	UPROPERTY(EditAnywhere, Category = Camera)
	FVector CameraOffset;

	UPROPERTY(EditAnywhere, Category = Camera)
	FRotator CameraRotation;

	/** First person camera */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = Camera,
		meta = (AllowPrivateAccess = "true")
	)
	UCameraComponent* FirstPersonCameraComponent;

	/** Move Input Action */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = Input,
		meta = (AllowPrivateAccess = "true")
	)
	UInputAction* MoveAction;

	/** Push Input Action */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = Input,
		meta = (AllowPrivateAccess = "true")
	)
	UInputAction* PushAction;

public:
	AEcsactUnrealFpsCharacter();

	auto IsMoveInputIgnored() const -> bool override;

protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor*              OtherActor,
		UPrimitiveComponent* OtherComp,
		int32                OtherBodyIndex,
		bool                 bFromSweep,
		const FHitResult&    SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor*              OtherActor,
		UPrimitiveComponent* OtherComp,
		int32                OtherBodyIndex
	);

public:
	// TODO: Use some kind of entity actor component
	ecsact_entity_id CharacterEntity = ECSACT_INVALID_ID(entity);
	int32            CharacterPlayerId = -1;

	auto SetMoveDirection(float X, float Y) -> void;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	void Push(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detect")
	USphereComponent* PushDetectionSphere;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent
	) override;
	// End of APawn interface

public:
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const {
		return FirstPersonCameraComponent;
	}
};
