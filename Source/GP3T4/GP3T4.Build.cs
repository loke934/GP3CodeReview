// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GP3T4 : ModuleRules
{
	public GP3T4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks", "FMODStudio", "UMG"});
	}
}
