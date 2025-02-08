
#pragma once
#include "MassEntityQuery.h"
#include "MassProcessor.h"

#include "MassBenchmarkProcessor.generated.h"

UCLASS()
class ECSACTBENCHMARK_API UMassBenchmarkProcessor : public UMassProcessor {
  GENERATED_BODY()

public:
  UMassBenchmarkProcessor();

protected:
  virtual void ConfigureQueries() override;
  virtual void Execute(FMassEntityManager &EntityManager,
                       FMassExecutionContext &Context) override;

private:
  FMassEntityQuery EntityQuery;
};
