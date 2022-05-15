// Copyright 1998-2022 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class GitPush: ModuleRules
{
  public GitPush(ReadOnlyTargetRules Target): base(Target)
  {
    PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

    PublicIncludePaths.AddRange(
      new string[] {
        Path.Combine(ModuleDirectory, "Public")
      }
    );

    PrivateIncludePaths.AddRange(
      new string[] {
        Path.Combine(ModuleDirectory, "Private")
      }
    );

    PublicDependencyModuleNames.AddRange(
      new string[] {
        "Core"
      }
    );

    PrivateDependencyModuleNames.AddRange(
      new string[] {
        "Projects",
        "InputCore",
        "UnrealEd",
        "LevelEditor",
        "CoreUObject",
        "Engine",
        "Slate",
        "SlateCore",
        "EditorStyle"
      }
    );

    DynamicallyLoadedModuleNames.AddRange(
      new string[] {
      }
    );
  }
}
