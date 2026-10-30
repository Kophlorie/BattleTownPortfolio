// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BattleTownPrototype : ModuleRules
{
	public BattleTownPrototype(ReadOnlyTargetRules Target) : base(Target)
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
			"BattleTownPrototype",
			"BattleTownPrototype/Variant_Platforming",
			"BattleTownPrototype/Variant_Platforming/Animation",
			"BattleTownPrototype/Variant_Combat",
			"BattleTownPrototype/Variant_Combat/AI",
			"BattleTownPrototype/Variant_Combat/Animation",
			"BattleTownPrototype/Variant_Combat/Gameplay",
			"BattleTownPrototype/Variant_Combat/Interfaces",
			"BattleTownPrototype/Variant_Combat/UI",
			"BattleTownPrototype/Variant_SideScrolling",
			"BattleTownPrototype/Variant_SideScrolling/AI",
			"BattleTownPrototype/Variant_SideScrolling/Gameplay",
			"BattleTownPrototype/Variant_SideScrolling/Interfaces",
			"BattleTownPrototype/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
