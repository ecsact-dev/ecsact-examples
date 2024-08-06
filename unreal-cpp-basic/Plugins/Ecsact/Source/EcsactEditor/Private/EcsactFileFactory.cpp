#include "EcsactFileFactory.h"
#include "Misc/Paths.h"

UEcsactFileFactory::UEcsactFileFactory() {
	bEditorImport = true;
	Formats.Add(TEXT("ecsact;Ecsact Package"));
}

auto UEcsactFileFactory::FactoryCanImport(const FString& Filename) -> bool {
	return FPaths::GetExtension(Filename).Equals(TEXT("ecsact"));
}

auto UEcsactFileFactory::FactoryCreateFile(
	UClass*           InClass,
	UObject*          InParent,
	FName             InName,
	EObjectFlags      Flags,
	const FString&    Filename,
	const TCHAR*      Parms,
	FFeedbackContext* Warn,
	bool&             bOutOperationCanceled
) -> UObject* {
	return nullptr;
}
