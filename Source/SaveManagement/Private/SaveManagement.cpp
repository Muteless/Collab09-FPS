#include "SaveManagement.h"

#include "LevelEditor.h"

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
	// MenuBuilder.AddMenuEntry(ToolBarResetSaveEntry, ToolBarResetSaveEntryTooltip)
}

void FSaveManagementModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSaveManagementModule, SaveManagement)