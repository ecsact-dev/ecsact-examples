using UnrealBuildTool;

public class Basic : ModuleRules {
	public Basic(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Ecsact",

			// TODO: these shouldn't be required
			"MassEntity",
			"MassActors",
			"MassSpawner",
		});
	}
}
