// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NeonRunnerTrials : ModuleRules
{
	public NeonRunnerTrials(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
