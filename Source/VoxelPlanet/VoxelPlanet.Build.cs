// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VoxelPlanet : ModuleRules
{
	public VoxelPlanet(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
