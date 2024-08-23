// Copyright (c) Yevhenii Selivanov

#include "LevelSequencerAudioTrimmerEdModule.h"
//---
#include "LevelSequence.h"
#include "ToolMenus.h"
#include "Modules/ModuleManager.h"
#include "Editor.h"

IMPLEMENT_MODULE(FLevelSequencerAudioTrimmerEdModule, LevelSequencerAudioTrimmer)

// Called right after the module DLL has been loaded and the module object has been created
void FLevelSequencerAudioTrimmerEdModule::StartupModule()
{
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLevelSequencerAudioTrimmerEdModule::RegisterMenus));
}

// Called before the module is unloaded, right before the module object is destroyed
void FLevelSequencerAudioTrimmerEdModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
}

// Registers the custom context menu item for Level Sequence assets
void FLevelSequencerAudioTrimmerEdModule::RegisterMenus()
{
	// Extend the context menu for Level Sequence assets
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.AssetContextMenu.LevelSequence");
	FToolMenuSection& Section = Menu->FindOrAddSection("AssetContextLevelSequence");
	Section.AddMenuEntry(
		"LevelSequencerAudioTrimmer",
		NSLOCTEXT("LevelSequencerAudioTrimmer", "LevelSequencerAudioTrimmer_Label", "Level Sequencer Audio Trimmer"),
		NSLOCTEXT("LevelSequencerAudioTrimmer", "LevelSequencerAudioTrimmer_Tooltip", "Trims audio tracks in the Level Sequence"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FLevelSequencerAudioTrimmerEdModule::OnLevelSequencerAudioTrimmerClicked))
	);
}

// Is called when Audio Trimmer button in clicked in the context menu of the Level Sequence asset
void FLevelSequencerAudioTrimmerEdModule::OnLevelSequencerAudioTrimmerClicked()
{
	// Get the selected assets from the content browser
	TArray<FAssetData> SelectedAssets;
	GEditor->GetContentBrowserSelections(SelectedAssets);

	for (const FAssetData& AssetData : SelectedAssets)
	{
		if (const ULevelSequence* LevelSequenceIt = Cast<ULevelSequence>(AssetData.GetAsset()))
		{
			AudioTrimmer.ProcessLevelSequence(*LevelSequenceIt);
		}
	}
}
