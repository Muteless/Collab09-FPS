#include "SaveManagement.h"
#include "LevelEditor.h"

#include "Kismet/GameplayStatics.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"

#define LOCTEXT_NAMESPACE "FSaveManagementModule"

void FSaveManagementModule::StartupModule()
{
	// Build the bar extension
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

	MenuExtender->AddMenuBarExtension(
		"Help",
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FSaveManagementModule::AddMenu)
		);
	
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FSaveManagementModule::AddMenu(FMenuBarBuilder& MenuBarBuilder)
{
	// Add pull down menu
	MenuBarBuilder.AddPullDownMenu(
		ToolBarMenuName,
		ToolBarMenuTooltip,
		FNewMenuDelegate::CreateRaw(this, &FSaveManagementModule::FillMenu)
		);
}

void FSaveManagementModule::FillMenu(FMenuBuilder& MenuBuilder)
{
	// Fill pull down menu
	MenuBuilder.AddMenuEntry(
		PullDownEntryResetSave,
		PullDownTooltipResetSave,
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(
				this,
				&FSaveManagementModule::DeleteSave),
				FCanExecuteAction()
				)
		);
}

void FSaveManagementModule::DeleteSave()
{
	// Get the full path of the save file
	FString SaveFilePath = FPaths::ProjectSavedDir() / TEXT("SaveGames") / SaveFileName;

	// Platform file manager to delete a file
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// check to see if save file exists
	if (PlatformFile.FileExists(*SaveFilePath))
	{
		if (PlatformFile.DeleteFile(*SaveFilePath))
		{
			UE_LOG(LogTemp, Log, TEXT("Save file deleted!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to delete save file!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Save file does not exist!"));
	}
}

void FSaveManagementModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSaveManagementModule, SaveManagement)