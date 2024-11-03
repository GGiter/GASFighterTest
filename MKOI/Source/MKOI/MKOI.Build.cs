// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MKOI : ModuleRules
{
	public MKOI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicIncludePaths.Add(ModuleDirectory + "/Public");

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "GameplayTags", "GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
