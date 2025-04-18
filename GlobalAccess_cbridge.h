#pragma once

#include <stdint.h>
#include <stdbool.h> // For bool type in C

// Forward declarations
struct ResourceControl;
struct CApp;
struct WorldManager;
struct BlueprintManager;
struct CrewMemberFactory;
struct SettingValues;

#ifdef __cplusplus
extern "C" {
#endif

ResourceControl* HS_Global_GetResources();
CApp* HS_Global_GetCApp();
WorldManager* HS_Global_GetWorld();
BlueprintManager* HS_Global_GetBlueprints();
CrewMemberFactory* HS_Global_GetCrewFactory();
SettingValues* HS_Global_GetSettings();
int HS_Globals_GetNextSpaceId();
bool HS_FileHelper_fileExists(const char* fileName);
bool HS_Settings_GetDlcEnabled();

#ifdef __cplusplus
}
#endif
