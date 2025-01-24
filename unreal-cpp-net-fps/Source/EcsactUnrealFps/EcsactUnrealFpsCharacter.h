// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "ecsact/runtime/common.h"

#include "EcsactUnrealFpsCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UEcsactUnrealExampleMovementComponent;
struct FInputActionValue;

UCLASS(config = Game)

class AEcsactUnrealFpsCharacter : public APawn {
	GENERATED_BODY()

	float MoveDirX;
	float MoveDirY;

	UPROPERTY(EditAnywhere, Category = Camera)
	FVector CameraOffset;

	UPROPERTY(EditAnywhere, Category = Camera)
	FRotator CameraRotation;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = Camera,
		meta = (AllowPrivateAccess = "true")
	)
	UCameraComponent* CameraComponent;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true")
	)
	UCapsuleComponent* RootCollision;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true")
	)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true")
	)
	UEcsactUnrealExampleMovementComponent* MovementComponent;

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

	UFUNCTION(BlueprintImplementableEvent)
	void OnPushChargeUpdated(float ChargePercentage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitPlayer(FExampleFpsPlayer Player);

	UFUNCTION(BlueprintCallable)
	static FLinearColor GetPlayerColour(int player_id);

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

	void StartPush(const FInputActionValue& Value);
	void FinishPush(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detect")
	USphereComponent* PushDetectionSphere;

protected:
	virtual auto SetupPlayerInputComponent( //
		UInputComponent* InputComponent
	) -> void override;
};
