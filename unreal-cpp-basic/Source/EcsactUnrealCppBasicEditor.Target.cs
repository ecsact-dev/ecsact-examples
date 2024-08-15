using UnrealBuildTool;

public class EcsactUnrealCppBasicEditorTarget : TargetRules {
	public EcsactUnrealCppBasicEditorTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("EcsactUnrealCppBasic");
		ExtraModuleNames.Add("EcsactEditor");
	}
}
