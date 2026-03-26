// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Prototyping_3C : ModuleRules
{
	public Prototyping_3C(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Prototyping_3C",
			"Prototyping_3C/Variant_Platforming",
			"Prototyping_3C/Variant_Platforming/Animation",
			"Prototyping_3C/Variant_Combat",
			"Prototyping_3C/Variant_Combat/AI",
			"Prototyping_3C/Variant_Combat/Animation",
			"Prototyping_3C/Variant_Combat/Gameplay",
			"Prototyping_3C/Variant_Combat/Interfaces",
			"Prototyping_3C/Variant_Combat/UI",
			"Prototyping_3C/Variant_SideScrolling",
			"Prototyping_3C/Variant_SideScrolling/AI",
			"Prototyping_3C/Variant_SideScrolling/Gameplay",
			"Prototyping_3C/Variant_SideScrolling/Interfaces",
			"Prototyping_3C/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
