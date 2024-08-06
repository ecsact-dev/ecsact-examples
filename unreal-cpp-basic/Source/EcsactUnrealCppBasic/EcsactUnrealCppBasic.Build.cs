using UnrealBuildTool;

public class EcsactUnrealCppBasic : ModuleRules {
	public EcsactUnrealCppBasic(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Ecsact",
		});
	}
}
