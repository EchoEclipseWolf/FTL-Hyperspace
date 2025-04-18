#pragma once

#include <stdint.h> // For size_t, standard integer types
#include <stdbool.h> // For bool type in C

// Define C-style enums and opaque pointers
typedef enum {
    C_TEMPORAL_ARM_NONE = 0,
    C_TEMPORAL_ARM_SPEED = 1,
    C_TEMPORAL_ARM_SLOW = 2
} CTemporalArmState;

typedef struct TemporalSystemWrapper* TemporalSystemWrapperPtr;
typedef struct ShipSystemExtend* ShipSystemExtendPtr;

#ifdef __cplusplus
extern "C" {
#endif

// TemporalSystemWrapper Functions
bool TemporalSystemWrapper_IsReady(TemporalSystemWrapperPtr wrapper);
CTemporalArmState TemporalSystemWrapper_GetArmed(TemporalSystemWrapperPtr wrapper);
int TemporalSystemWrapper_GetRealDilation(TemporalSystemWrapperPtr wrapper);
void TemporalSystemWrapper_SetArmed(TemporalSystemWrapperPtr wrapper, CTemporalArmState newArmState);
void TemporalSystemWrapper_StartTimeDilation(TemporalSystemWrapperPtr wrapper, int shipId, int roomId, bool speedUp);
void TemporalSystemWrapper_StopTimeDilation(TemporalSystemWrapperPtr wrapper);

// ShipSystemExtend Functions
TemporalSystemWrapperPtr ShipSystemExtend_GetTemporalSystemWrapper(ShipSystemExtendPtr extend);
int ShipSystemExtend_GetAdditionalPowerLoss(ShipSystemExtendPtr extend);
void ShipSystemExtend_SetAdditionalPowerLoss(ShipSystemExtendPtr extend, int loss);
int ShipSystemExtend_GetOverclockEffect(ShipSystemExtendPtr extend);

// Getter for the _Extend object
ShipSystemExtendPtr Get_ShipSystem_Extend_C(void* shipSystemPtr);

// Opaque Pointers
typedef struct ProjectileExtend* ProjectileExtendPtr;
typedef struct CustomDamageDefinition* CCustomDamageDefinitionPtr; // Opaque for definition
typedef struct WeaponBlueprint* WeaponBlueprintPtr; // Opaque for WeaponBlueprint
typedef struct Projectile* ProjectilePtr; // Opaque for Projectile

// C-Style Structs
// Simplified CCustomDamage - only exposing the definition pointer for now
typedef struct CCustomDamage {
    CCustomDamageDefinitionPtr definition; // Pointer to the definition's C representation
    int sourceShipId;
} CCustomDamage;

// Simplified CCustomDamageDefinition - exposing only a few fields
typedef struct CCustomDamageDefinition {
    int idx;
    int accuracyMod; // This is definition's base accuracyMod
    int droneAccuracyMod; // This is definition's base droneAccuracyMod
    bool noSysDamage;
    bool noPersDamage;
    // Skipping vectors and complex types for now
} CCustomDamageDefinition;

// Simplified CTextString (assuming it holds char*)
typedef struct CTextString {
     const char* text;
} CTextString;

// Simplified CCustomWeaponDefinition
typedef struct CCustomWeaponDefinition {
    const char* name;
    int freeMissileChance;
    CTextString descriptionOverride; // Assuming direct mapping
    // ... other simple fields ...
    bool hideEventTooltip;
    bool invisibleBeam;
    bool simultaneousFire;
    float fireTime;
    float angularRadius;
    int shotLimit;
    const char* iconReplace;
    float iconScale;
    CCustomDamageDefinitionPtr customDamage; // Pointer to opaque definition struct
    // Skipping map for miniProjectileOverride
} CCustomWeaponDefinition;

// ProjectileExtend Functions
const char* ProjectileExtend_GetName(ProjectileExtendPtr extend); // Returns pointer to internal string data
void ProjectileExtend_GetCustomDamage(ProjectileExtendPtr extend, CCustomDamage* outDamage); // Copies data to C struct
int ProjectileExtend_GetCustomDamageAccuracyMod(ProjectileExtendPtr extend); // Getter for accuracyMod in Projectile_Extend::customDamage
void ProjectileExtend_SetCustomDamageAccuracyMod(ProjectileExtendPtr extend, int mod); // Setter for accuracyMod
int ProjectileExtend_GetCustomDamageDroneAccuracyMod(ProjectileExtendPtr extend); // Getter for droneAccuracyMod
void ProjectileExtend_SetCustomDamageDroneAccuracyMod(ProjectileExtendPtr extend, int mod); // Setter for droneAccuracyMod
// Missed Drones (vector<int>) - Getter functions
int* ProjectileExtend_GetMissedDronesData(ProjectileExtendPtr extend); // Returns direct pointer (use with caution)
size_t ProjectileExtend_GetMissedDronesSize(ProjectileExtendPtr extend);

// Getter for the _Extend object
ProjectileExtendPtr Get_Projectile_Extend_C(ProjectilePtr projectilePtr);

// CustomDamageDefinition Functions (Accessing via CCustomDamageDefinitionPtr)
int CustomDamageDefinition_GetIdx(CCustomDamageDefinitionPtr def);
int CustomDamageDefinition_GetAccuracyMod(CCustomDamageDefinitionPtr def);
// ... other getters for CCustomDamageDefinition fields ...

// CustomWeaponManager Functions
const CCustomWeaponDefinition* CustomWeaponManager_GetWeaponDefinition(const char* bpName); // Returns pointer to C struct (lifetime managed by C++)
void CustomWeaponManager_ProcessMiniProjectile(ProjectilePtr projectilePtr, WeaponBlueprintPtr weaponBlueprintPtr, int boostLevel);

// Enums
typedef enum {
    C_DRONE_AI_SYSTEMS,
    C_DRONE_AI_SYSTEMS_POWER,
    C_DRONE_AI_CREW_HEAL,
    C_DRONE_AI_ENEMIES
} CDroneAbilityAIType;

typedef enum {
    C_INHERIT_MODE_FORCE_OLD,
    C_INHERIT_MODE_ASK_PLAYER,
    C_INHERIT_MODE_FORCE_NEW
} CInheritMode;

// C-Style Structs
typedef struct CDroneAbilityDefinition {
    int delay;
    CDroneAbilityAIType ai;
} CDroneAbilityDefinition;

typedef struct CCustomDroneDefinition {
    const char* name; // Read-only pointer
    const char* tooltipName; // Read-only pointer
    const char* crewBlueprint; // Read-only pointer
    bool hasAbility;
    CDroneAbilityDefinition ability; // Embed struct
} CCustomDroneDefinition;

// Opaque pointer for the manager singletons (optional, could just use static calls)
typedef struct CustomDroneManager* CustomDroneManagerPtr;
typedef struct SaveFileHandler* SaveFileHandlerPtr;


// CustomDroneManager Functions
// CustomDroneManagerPtr CustomDroneManager_GetInstance_C(); // Optional: Get manager instance ptr
const CCustomDroneDefinition* CustomDroneManager_GetDefinition(const char* droneName); // Returns pointer to C struct cache
const CCustomDroneDefinition* CustomDroneManager_GetDefinitionByRace(const char* raceName); // Returns pointer to C struct cache

// SaveFileHandler Functions
// SaveFileHandlerPtr SaveFileHandler_GetInstance_C(); // Optional: Get manager instance ptr
void SaveFileHandler_CreateTransferFile();
void SaveFileHandler_DeleteTransferFile();
bool SaveFileHandler_TransferFileExists();
const char* SaveFileHandler_GetSavePrefix();
void SaveFileHandler_SetSavePrefix(const char* prefix);
bool SaveFileHandler_GetFirstTime();
void SaveFileHandler_SetFirstTime(bool value);
bool SaveFileHandler_GetWelcomeDialog();
void SaveFileHandler_SetWelcomeDialog(bool value);
CInheritMode SaveFileHandler_GetInheritMode();
void SaveFileHandler_SetInheritMode(CInheritMode mode);
// int SaveFileHandler_GetVersion(); // Static const, likely not needed via binding


#ifdef __cplusplus
} // extern "C"
#endif
