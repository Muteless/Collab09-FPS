#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSaveManagement, All, All);

class FSaveManagementModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    FText ToolBarMenuName = FText::FromString("Save Manager");
    FText ToolBarMenuTooltip = FText::FromString("Save file editing tools");
    
    FText ToolBarResetSaveEntry = FText::FromString("Reset Save");
    FText ToolBarResetSaveEntryTooltip = FText::FromString("Resets the save at the current slot");
    
    // Adds menu to toolbar
    void AddMenu(FMenuBarBuilder& MenuBarBuilder);

    // Populates menu in toolbar
    void FillMenu(FMenuBuilder& MenuBuilder);
};
