#include "GlobalAccess_cbridge.h"
#include "Global.h"         // For G_ and Globals::GetNextSpaceId()
#include "FTLGameWin32.h"   // For FileHelper::fileExists and Settings::GetDlcEnabled() and potentially manager types
#include <string>           // For std::string conversion in fileExists

extern "C" {

ResourceControl* HS_Global_GetResources() {
    return G_->GetResources();
}

CApp* HS_Global_GetCApp() {
    return G_->GetCApp();
}

WorldManager* HS_Global_GetWorld() {
    return G_->GetWorld();
}

BlueprintManager* HS_Global_GetBlueprints() {
    return G_->GetBlueprints();
}

CrewMemberFactory* HS_Global_GetCrewFactory() {
    return G_->GetCrewFactory();
}

SettingValues* HS_Global_GetSettings() {
    return G_->GetSettings();
}

int HS_Globals_GetNextSpaceId() {
    // Assuming Globals is a namespace or class with a static method GetNextSpaceId
    return Globals::GetNextSpaceId();
}

bool HS_FileHelper_fileExists(const char* fileName) {
    // Assuming FileHelper is a namespace or class with a static method fileExists
    return FileHelper::fileExists(std::string(fileName));
}

bool HS_Settings_GetDlcEnabled() {
    // Assuming Settings is a namespace or class with a static method GetDlcEnabled
    return Settings::GetDlcEnabled();
}

} // extern "C"
