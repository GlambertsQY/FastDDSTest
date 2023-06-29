// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class FastDDSTest : ModuleRules
{
	public FastDDSTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		string fastrtpsHome = Environment.GetEnvironmentVariable("FASTRTPSHOME");
		
		PublicIncludePaths.Add(Path.Combine(fastrtpsHome, "include"));
		
		PublicAdditionalLibraries.Add(Path.Combine(fastrtpsHome, "lib/x64Win64VS2019/fastcdr-1.0.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(fastrtpsHome, "lib/x64Win64VS2019/fastrtps-2.10.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(fastrtpsHome, "lib/x64Win64VS2019/foonathan_memory-0.7.3.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(fastrtpsHome, "lib/x64Win64VS2019/libfastrtps-2.10.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(fastrtpsHome, "lib/x64Win64VS2019/libfastcdr-1.0.lib"));
	}
}
