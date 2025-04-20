// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DaoFa : ModuleRules
{
	public DaoFa(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","Niagara", "Slate", "SlateCore", "UMG" ,"Json" ,"JsonUtilities", "UnrealEd" });
	}
}
