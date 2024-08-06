#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EcsactFileFactory.generated.h"

UCLASS()
class UEcsactFileFactory : public UFactory {
	GENERATED_BODY()

public:
	UEcsactFileFactory();

	auto FactoryCanImport(const FString& Filename) -> bool override;
	auto FactoryCreateFile(
		UClass*           InClass,
		UObject*          InParent,
		FName             InName,
		EObjectFlags      Flags,
		const FString&    Filename,
		const TCHAR*      Parms,
		FFeedbackContext* Warn,
		bool&             bOutOperationCanceled
	) -> UObject* override;
};
