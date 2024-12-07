#include "MassCommands.h"
#include "MassCommonFragments.h"
#include "MassEntityTypes.h"
#include "EcsactUnrealFps/Fragments/EcsactFragments.h"

struct FTransformUpdateCommand : public FMassBatchedCommand {
	using Super = FMassBatchedCommand;

	FTransformUpdateCommand() : Super(EMassCommandOperationType::Set) {
	}

	void Add(auto EntityHandle, FTransform InTransform) {
		UE_LOG(LogTemp, Warning, TEXT("ADDERONIS TRASNFORM?"));
		Entities.Add(EntityHandle);
		EntityTransforms.Add(InTransform);
	}

protected:
	virtual void Execute(FMassEntityManager& Manager) const override {
		UE_LOG(LogTemp, Warning, TEXT("UPDATEING DAT TRANSFORM KEKEKE"));
		for(int i = 0; i < Entities.Num(); ++i) {
			auto Entity = Entities[i];
			auto Transform = EntityTransforms[i];

			auto* EntityTransform =
				Manager.GetFragmentDataPtr<FTransformFragment>(Entity);
			EntityTransform->SetTransform(Transform);
		}
	}

	virtual SIZE_T GetAllocatedSize() const override {
		return EntityTransforms.GetAllocatedSize() + Entities.GetAllocatedSize();
	}

#if CSV_PROFILER || WITH_MASSENTITY_DEBUG
	virtual int32 GetNumOperationsStat() const override {
		return Entities.Num();
	}
#endif

private:
	TArray<FMassEntityHandle> Entities;
	TArray<FTransform>        EntityTransforms;
};

struct FEcsactPositionUpdateCommand : public FMassBatchedCommand {
	using Super = FMassBatchedCommand;

	FEcsactPositionUpdateCommand() : Super(EMassCommandOperationType::Set) {
	}

	void Add(auto EntityHandle, FVector EntityPos) {
		Entities.Add(EntityHandle);
		EntityPositions.Add(EntityPos);
	}

protected:
	virtual void Execute(FMassEntityManager& Manager) const override {
		UE_LOG(LogTemp, Warning, TEXT("UPDATEING DAT POS KEKEKE"));
		for(int i = 0; i < Entities.Num(); ++i) {
			auto Entity = Entities[i];
			auto Position = EntityPositions[i];

			auto* EntityPosition =
				Manager.GetFragmentDataPtr<FEcsactPositionFragment>(Entity);
			EntityPosition->SetPosition(Position);
		}
	}

	virtual SIZE_T GetAllocatedSize() const override {
		return EntityPositions.GetAllocatedSize() + Entities.GetAllocatedSize();
	}

#if CSV_PROFILER || WITH_MASSENTITY_DEBUG
	virtual int32 GetNumOperationsStat() const override {
		return Entities.Num();
	}
#endif

private:
	TArray<FMassEntityHandle> Entities;
	TArray<FVector>           EntityPositions;
};
