using UnrealBuildTool;

public class CustomCodegen : ModuleRules {
	public CustomCodegen(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine", "InputCore",
			"EnhancedInput",
			"Ecsact",
		});
		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
