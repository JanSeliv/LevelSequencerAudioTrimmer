import os
import sys
import unreal

def get_file_size_mb(path):
    """Returns the size of the file in MB."""
    size_in_bytes = os.path.getsize(path) if os.path.exists(path) else 0
    size_in_mb = size_in_bytes / (1024 * 1024)
    return size_in_mb

def process_audio(level_sequence_path):
    """Processes each audio section in the level sequence."""
    level_sequence = unreal.EditorAssetLibrary.load_asset(level_sequence_path)
    if not level_sequence:
        unreal.log_error(f"Failed to load Level Sequence: {level_sequence_path}")
        return

    unreal.log(f"Loaded Level Sequence: {level_sequence_path}")

    audio_sections = unreal.AudioTrimmerUtilsLibrary.get_audio_sections(level_sequence)
    if not audio_sections:
        unreal.log_error("No audio sections found in the level sequence.")
        return

    unreal.log(f"Found {len(audio_sections)} audio sections.")

    for audio_section in audio_sections:
        sound_wave = audio_section.get_sound()
        if not sound_wave:
            unreal.log_warning(f"Failed to get SoundWave from AudioSection. Skipping...")
            continue

        # Export the sound wave to a temporary WAV file
        export_path = unreal.AudioTrimmerUtilsLibrary.export_sound_wave_to_wav(sound_wave)
        if not export_path:
            unreal.log_warning(f"Failed to export {sound_wave.get_name()}. Skipping...")
            continue

        # Calculate trim times
        start_time_ms, end_time_ms = unreal.AudioTrimmerUtilsLibrary.calculate_trim_times(level_sequence, audio_section)
        start_time_sec = start_time_ms / 1000.0
        end_time_sec = end_time_ms / 1000.0

        trimmed_audio_path = export_path.replace(".wav", "_trimmed.wav")

        # Trim the audio using the C++ function
        if not unreal.AudioTrimmerUtilsLibrary.trim_audio(export_path, trimmed_audio_path, start_time_sec, end_time_sec):
            unreal.log_warning(f"Trimming audio failed for {sound_wave.get_name()}. Skipping...")
            continue

        # Reimport the trimmed audio into the original sound wave asset using FReimportManager
        if not unreal.AudioTrimmerUtilsLibrary.reimport_audio_to_unreal(sound_wave, trimmed_audio_path):
            unreal.log_warning(f"Reimporting trimmed audio failed for {sound_wave.get_name()}. Skipping...")
            continue

        # Reset the Start Frame Offset for this audio section
        unreal.AudioTrimmerUtilsLibrary.reset_start_frame_offset(audio_section)

        # Delete the temporary exported WAV file
        unreal.AudioTrimmerUtilsLibrary.delete_temp_wav_file(export_path)
        unreal.AudioTrimmerUtilsLibrary.delete_temp_wav_file(trimmed_audio_path)

    unreal.log("Processing complete.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        unreal.log_error("Usage: py audio_reimporter.py <LevelSequencePath>")
    else:
        level_sequence_path = sys.argv[1]
        process_audio(level_sequence_path)
