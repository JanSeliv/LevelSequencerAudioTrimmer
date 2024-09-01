﻿// Copyright (c) Yevhenii Selivanov

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
//---
#include "AudioTrimmerUtilsLibrary.generated.h"

class UMovieSceneAudioSection;
class ULevelSequence;
class USoundWave;

struct FTrimTimes;

DEFINE_LOG_CATEGORY_STATIC(LogAudioTrimmer, Log, All);

typedef TMap<FTrimTimes, TArray<UMovieSceneAudioSection*>> FTrimTimesMap;
typedef TMap<USoundWave*, FTrimTimesMap> FSoundsTrimTimesMap;

/**
 * Utility library for handling audio trimming and reimporting in Unreal Engine.
 */
UCLASS()
class LEVELSEQUENCERAUDIOTRIMMERED_API UAudioTrimmerUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Entry method to run the main flow of trimming all audio assets for the given level sequence.
	 * - Trims audio assets based on their usage in given Level Sequence to reduce the file size.
	 * - Reuses already trimmed audio assets if they are used multiple times with the same trim times.
	 * - Duplicates sound waves if needed to handle multiple instances of the same audio with different trim times. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer")
	static void RunLevelSequenceAudioTrimmer(const ULevelSequence* LevelSequence);

	/*********************************************************************************************
	 * Preprocessing
	 * Prepares the `SoundsTrimTimesMap` map that combines sound waves with their corresponding trim times.
	 ********************************************************************************************* */
public:
	/** Prepares a map of sound waves to their corresponding trim times based on the audio sections used in the given level sequence.
	 * @param OutSoundsTrimTimesMap Combines and returns a map of sound waves to their corresponding trim times.
	 * @param LevelSequence The main level sequence to search for audio sections. */
	static void HandleSoundsInRequestedLevelSequence(FSoundsTrimTimesMap& OutSoundsTrimTimesMap, const ULevelSequence* LevelSequence);

	/** Handles those sounds from requested Level Sequence that are used at the same time in other Level Sequences.
	* @param InOutSoundsTrimTimesMap Takes the map of sound waves and adds the trim times with sections of the sound waves that are used in other sequences. */
	static void HandleSoundsInOtherSequences(FSoundsTrimTimesMap& InOutSoundsTrimTimesMap);

	/** Main goal of this function is to handle those sounds that are used outside of level sequences like in the world or blueprints.
	 * @param InOutSoundsTrimTimesMap Takes the map of sound waves and modifies it if matches found with external used sounds.  */
	static void HandleSoundsOutsideSequences(FSoundsTrimTimesMap& InOutSoundsTrimTimesMap);

	/*********************************************************************************************
	 * Main Flow
	 * Is called after the preprocessing for each found audio.
	 ********************************************************************************************* */
public:
	/** Duplicates the given SoundWave asset, incrementing an index to its name.
	 * Useful for handling multiple instances of the same audio with different trim times.
	 * @param OriginalSoundWave The original SoundWave asset to duplicate.
	 * @param DuplicateIndex The index to append to the duplicated asset's name.
	 * @return Duplicated Sound Wave asset in the same directory as the original asset. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer")
	static USoundWave* DuplicateSoundWave(USoundWave* OriginalSoundWave, int32 DuplicateIndex = 1);

	/** Exports a sound wave to a WAV file.
	 * @param SoundWave The sound wave to export.
	 * @return The file path to the exported WAV file. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer")
	static FString ExportSoundWaveToWav(USoundWave* SoundWave);

	/** Trims an audio file to the specified start and end times.
	 * @param TrimTimes The start and end times in milliseconds to trim the audio file to.
	 * @param InputPath The file path to the audio file to trim.
	 * @param OutputPath The file path to save the trimmed audio file.
	 * @return True if the audio was successfully trimmed, false otherwise. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer", meta = (AutoCreateRefTerm = "TrimTimes", InputPath, OutputPath))
	static bool TrimAudio(const FTrimTimes& TrimTimes, const FString& InputPath, const FString& OutputPath);

	/** Reimports an audio file into the original sound wave asset in Unreal Engine.
	 * @param OriginalSoundWave The original sound wave asset to be reimported.
	 * @param TrimmedAudioFilePath The file path to the trimmed audio file.
	 * @return True if the reimport was successful, false otherwise. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer")
	static bool ReimportAudioToUnreal(USoundWave* OriginalSoundWave, const FString& TrimmedAudioFilePath);

	/** Resets the start frame offset of an audio section to 0 and sets a new sound wave.
	 * @param AudioSection The audio section to modify.
	 * @param NewSound The new sound wave to set for the audio section. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer")
	static void ResetTrimmedAudioSection(UMovieSceneAudioSection* AudioSection, USoundWave* NewSound);

	/** Deletes a temporary WAV file from the file system. * 
	 * @param FilePath The file path of the WAV file to delete.
	 * @return True if the file was successfully deleted, false otherwise. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer")
	static bool DeleteTempWavFile(const FString& FilePath);

	/*********************************************************************************************
	 * Utilities
	 ********************************************************************************************* */
public:
	/** Retrieves all audio sections from the given level sequence.
	 * @param OutMap Returns a map of sound waves to their corresponding audio sections, where the same sound wave can be used in multiple audio sections.
	 * @param InLevelSequence The level sequence to search for audio sections. */
	static void FindAudioSectionsInLevelSequence(TMap<USoundWave*, TArray<UMovieSceneAudioSection*>>& OutMap, const ULevelSequence* InLevelSequence);

	/** Finds all assets that directly reference the given sound wave.
	* @param OutUsages Returns the found assets that reference the sound wave.
	* @param InSound The sound wave asset to find usages for. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer")
	static void FindAudioUsagesBySoundAsset(TArray<UObject*>& OutUsages, const USoundWave* InSound);

	/** Calculates the start and end times in milliseconds for trimming multiple audio sections.
	 * @param OutTrimTimesMap Returns a map of audio sections to their corresponding trim times.
	 * @param AudioSections The audio sections to calculate trim times for. */
	static void CalculateTrimTimes(FTrimTimesMap& OutTrimTimesMap, const TArray<UMovieSceneAudioSection*>& AudioSections);

	/** Calculates the start and end times in milliseconds for trimming an audio section.
	 * @param AudioSection The audio section to calculate trim times for.
	 * @return A struct containing the start and end times in milliseconds. */
	UFUNCTION(BlueprintCallable, Category = "Audio Trimmer")
	static FTrimTimes CalculateTrimTimes(UMovieSceneAudioSection* AudioSection);
};
