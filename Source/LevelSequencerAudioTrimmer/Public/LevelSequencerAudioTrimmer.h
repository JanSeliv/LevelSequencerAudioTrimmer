// Copyright (c) Yevhenii Selivanov

#pragma once

/**
 * Handles audio trimming in Level Sequences.
 */
class FLevelSequencerAudioTrimmer
{
public:
	/** Main entry point for the Level Sequencer Audio Trimmer plugin. */
	void ProcessLevelSequence(const class ULevelSequence& LevelSequence);
};
