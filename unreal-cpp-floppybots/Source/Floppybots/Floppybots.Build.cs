// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Floppybots : ModuleRules {
	public Floppybots(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreOnline",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Ecsact",
			"EcsactNet",
			"EcsactNetWasm",
			"StructUtils",
			"MassSpawner",
			"MassAIBehavior",
			"StateTreeModule",
			"MassNavigation",
			"NavigationSystem",
			"MassEntity",
			"MassCommon",
			"MassSignals",
			"MassMovement",
			"MassRepresentation",
			"MassActors",
		});
	}
}
