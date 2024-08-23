# AudioTrimmerUtilsLibrary

**AudioTrimmerUtilsLibrary** is a utility plugin designed to simplify the process of trimming and managing audio assets within Unreal Engine. With this plugin, you can easily trim all audio sections in a level sequence with a single click, streamlining your workflow and optimizing sound resources in your projects.

## Features

- **One-Click Trimming**: Trim all audio sections in a level sequence with a single click, significantly speeding up the audio optimization process.
- **Trim Time Calculation**: Automatically calculate the start and end times for trimming audio sections based on their usage in the level sequence.
- **WAV Export**: Export sound waves to WAV files for external processing.
- **Audio Reimport**: Reimport trimmed audio files back into Unreal Engine, updating the original sound wave assets.
- **Reset Audio Offsets**: Automatically reset the start frame offsets for audio sections after reimporting, ensuring proper synchronization.
- **Temporary File Management**: Automatically delete temporary WAV files after they have been processed, keeping your project clean and organized.

## Installation

1. Clone or download the repository into the `Plugins` folder of your Unreal Engine project.
2. Open your Unreal Engine project.
3. Go to `Edit > Plugins`, find the **AudioTrimmerUtilsLibrary** plugin, and enable it.
4. Restart your Unreal Engine project.

## Usage

### Trimming All Audio Sections in a Level Sequence

To trim all audio sections in a level sequence:

1. Ensure your level sequence is correctly set up with audio sections.
2. Open `Output Window` in Unreal Engine
3. In `cmd` line, execute `audio_reimporter.py ` script with argument as reference to the Level Sequence:
   ```bash
   py "YourUnrealProject/Plugins/AudioTrimmerUtilsLibrary/Python/audio_reimporter.py" "/Game/Path/To/Your/LevelSequence"
