// Copyright (c) Yevhenii Selivanov.

#pragma once

#include "Modules/ModuleInterface.h"
//---
#include "CoreMinimal.h"
//---
#include "LevelSequencerAudioTrimmer.h"

class LEVELSEQUENCERAUDIOTRIMMERED_API FLevelSequencerAudioTrimmerEdModule : public IModuleInterface
{
public:
	/**
	 * Called right after the module DLL has been loaded and the module object has been created.
	 * Load dependent modules here, and they will be guaranteed to be available during ShutdownModule.
	 */
	virtual void StartupModule() override;

	/**
	* Called before the module is unloaded, right before the module object is destroyed.
	* During normal shutdown, this is called in reverse order that modules finish StartupModule().
	* This means that, as long as a module references dependent modules in it's StartupModule(), it
	* can safely reference those dependencies in ShutdownModule() as well.
	*/
	virtual void ShutdownModule() override;

	/** Registers the custom context menu item for Level Sequence assets. */
	void RegisterMenus();

	/** Is called when Audio Trimmer button in clicked in the context menu of the Level Sequence asset. */
	void OnLevelSequencerAudioTrimmerClicked();

protected:
	/** Audio trimmer instance */
	FLevelSequencerAudioTrimmer AudioTrimmer;

	/*********************************************************************************************
	 * Plugin name/path
	 ********************************************************************************************* */
public:
	inline static const FString PluginName = TEXT("LevelSequencerAudioTrimmer");

	/** Returns the full path to this plugin. */
	static const FString& GetPluginPath() { return PluginPath; }

protected:
	/** Sets this plugin full path. */
	void InitPluginPath();

	/** Current full path to this plugin. */
	static FString PluginPath;

	/*********************************************************************************************
	 * FFMPEG
	 ********************************************************************************************* */
public:
	/** Returns the full path to the FFMPEG library stored in this plugin. */
	static const FString& GetFfmpegPath() { return FfmpegPath; }

protected:
	/** Sets FFMPEG path depending on the platform. */
	void InitFfmpegPath();

	/** Current path to the FFMPEG library. */
	static FString FfmpegPath;
};
