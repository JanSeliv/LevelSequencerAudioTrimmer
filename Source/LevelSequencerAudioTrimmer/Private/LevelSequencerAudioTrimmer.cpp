// Copyright (c) Yevhenii Selivanov

#include "LevelSequencerAudioTrimmer.h"
//---
#include "LevelSequencerAudioTrimmerEdModule.h"
//---
#include "AudioTrimmerUtilsLibrary.h"
#include "LevelSequence.h"
#include "IPythonScriptPlugin.h"

// Main entry point for the Level Sequencer Audio Trimmer plugin
void FLevelSequencerAudioTrimmer::ProcessLevelSequence(const ULevelSequence& LevelSequence)
{
	const FString& CurrentPluginLocation = FLevelSequencerAudioTrimmerEdModule::GetPluginPath();
	const FString PythonScriptPath = FPaths::Combine(CurrentPluginLocation, TEXT("Python"), TEXT("audio_reimporter.py"));
	const FString LevelSequencePath = LevelSequence.GetPathName();
	const FString PythonCommand = FString::Printf(TEXT("import sys; sys.argv = ['%s', '%s']; exec(open('%s').read())"), *PythonScriptPath, *LevelSequencePath, *PythonScriptPath);

	// Execute the Python script
	const bool bExecuted = IPythonScriptPlugin::Get()->ExecPythonCommand(*PythonCommand);
	UE_LOG(LogAudioTrimmer, Log, TEXT("%s"), bExecuted ? TEXT("Successfully executed the Python script.") : TEXT("Failed to execute the Python script."));
}
