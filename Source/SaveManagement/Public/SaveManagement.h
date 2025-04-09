#pragma once

#ifdef WITH_EDITOR

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSaveManagement, All, All);

class FSaveManagementModule : public IModuleInterface
{

public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    #pragma region ToolBar

    FText ToolBarMenuName = FText::FromString("Save Manager");
    FText ToolBarMenuTooltip = FText::FromString("Save file editing tools");
    
    FText PullDownEntryResetSave = FText::FromString("Delete Save");
    FText PullDownTooltipResetSave = FText::FromString("Delete the default save file");
    
    // Adds menu to toolbar
    void AddMenu(FMenuBarBuilder& MenuBarBuilder);

    // Populates menu in toolbar
    void FillMenu(FMenuBuilder& MenuBuilder);

	#pragma region Actions

	const FString SaveFileName = "Default.sav";
	void DeleteSave();

	#pragma endregion Actions
    
    #pragma endregion ToolBar


};
#endif