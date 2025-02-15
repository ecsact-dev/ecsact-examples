#pragma once

#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "Floppybots/Floppybots__ecsact__ue.h"
#include "Floppybots/EcsactPlayerEntitySpawner.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "ecsact/runtime/common.h"
#include "Floppybots__ecsact__ue.h"

#include "FloppybotsCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UFloppybotsMovementComponent;
struct FInputActionValue;

UCLASS(config = Game)

class AFloppybotsCharacter : public APawn {
	GENERATED_BODY()

	friend class UEcsactPlayerEntitySpawner;

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
	UFloppybotsMovementComponent* MovementComponent;

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
	AFloppybotsCharacter();

	auto IsMoveInputIgnored() const -> bool override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPushChargeUpdated(float ChargePercentage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitPlayer(FFloppybotsPlayer Player);

	/**
	 * Get the deterministic generated colour for the given player ID. Will always
	 * return the same colour with the same player ID.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ecsact Unreal Example")
	static FLinearColor GetPlayerColour(int player_id);

protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitPushcharge(FFloppybotsPushcharge Pushcharge);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdatePushcharge(FFloppybotsPushcharge Pushcharge);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemovePushcharge(FFloppybotsPushcharge Pushcharge);

public:
	// TODO: Use some kind of entity actor component
	ecsact_entity_id CharacterEntity = ECSACT_INVALID_ID(entity);
	int32 CharacterPlayerId = -1;

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
