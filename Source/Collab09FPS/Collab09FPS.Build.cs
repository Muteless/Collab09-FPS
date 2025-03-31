// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Collab09FPS : ModuleRules
{
	public Collab09FPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Niagara", "AIModule", 
			"NavigationSystem",
			"Kismet" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});
		
		PrivateIncludePaths.AddRange(new string[] { "Collab09FPS/Private" });
		PublicIncludePaths.AddRange(new string[] { "Collab09FPS/Public" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
