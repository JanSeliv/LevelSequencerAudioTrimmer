// Copyright (c) Yevhenii Selivanov

using UnrealBuildTool;
using System.IO;

public class LevelSequencerAudioTrimmerEd : ModuleRules
{
	public LevelSequencerAudioTrimmerEd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;
		bEnableNonInlinedGenCppWarnings = true;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject", "Engine", "Slate", "SlateCore" // Core
				, "MovieSceneTracks" // UMovieSceneAudioSection
				, "MovieScene"
				, "LevelSequence"
				, "UnrealEd" // FReimportManager
				, "ToolMenus"
			}
		); 

		// @TODO Remove once Python script execution is completely rewritten to C++ 
		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"Projects" // FindPlugin
				, "PythonScriptPlugin" // FPythonScriptPlugin
			}
		);

		// Adding FFMPEG ThirdParty dependency
        var FFMPEGPath = Path.Combine(ModuleDirectory, "..", "ThirdParty", "ffmpeg");
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            RuntimeDependencies.Add(Path.Combine(FFMPEGPath, "Windows", "ffmpeg.exe"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.Linux)
        {
            RuntimeDependencies.Add(Path.Combine(FFMPEGPath, "Linux", "ffmpeg"));
        }
	}
}
