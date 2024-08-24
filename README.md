# Level Sequencer Audio Trimmer

**Level Sequencer Audio Trimmer** is a utility plugin for Windows, MacOS and Linux that is designed to automatically trim and reimport all audio assets in a level sequence with a single click, streamlining your workflow and optimizing sound resources in your projects.

## Usage

1. Right-click on the desired Level Sequence asset in the Content Browser.
2. Select `Level Sequencer Audio Trimmer` from the context menu.
3. The action will be executed and all audio in the Level Sequence will be trimmed.

![ContextMenu](https://github.com/user-attachments/assets/116b4a7f-6d19-4354-9013-0dfc3c8f6358)

## Features

- **One-Click Trimming**: Trim all audio sections in a level sequence with a single click, significantly speeding up the audio optimization process.
- **Trim Time Calculation**: Automatically calculate the start and end times for trimming audio sections based on their usage in the level sequence.
- **Audio Reimport**: Reimport trimmed audio files back into Unreal Engine, updating the original sound wave assets.
- **Reset Audio Offsets**: Automatically reset the start frame offsets for audio sections after reimporting, ensuring proper synchronization.

## Installation

1. Clone or download the repository into the `Plugins` folder of your Unreal Engine project.
2. Open your Unreal Engine project.
3. Go to `Edit > Plugins`, find the **AudioTrimmerUtilsLibrary** plugin, and enable it.
4. Restart your Unreal Engine project.
