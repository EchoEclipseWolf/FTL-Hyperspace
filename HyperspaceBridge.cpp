#include "HyperspaceBridge.h"

// Includes from Subtask 1
#include "System_Extend.h" // Include the actual C++ header
#include "FTLGame.h"       // Include base types if needed (like ShipSystem)
#include <stdexcept>       // For error handling if needed

// Includes from Subtask 2
#include "Projectile_Extend.h"
#include "CustomWeapons.h"
#include "CustomDamage.h"
#include "Resources.h" // For TextString? (Guessing) - Adjust includes as needed

// Includes from Subtask 3
#include "CustomDrones.h"
#include "AbilityDrone.h" // Needed for DroneAbilityDefinition
#include "SaveFile.h"


// Basic null check helper (from Subtask 1)
template<typename T>
void check_pointer(T* ptr, const char* functionName) {
    if (!ptr) {
        // Consider logging instead of throwing exceptions across C boundary
        // For now, just return or handle gracefully in the function
        // throw std::runtime_error(std::string(functionName) + ": received null pointer");
    }
}

// Helper to convert std::string to const char* (from Subtask 2, needed by Subtask 3 too)
// Note: This is potentially unsafe if the std::string is temporary.
// A safer approach involves copying to a C#-managed buffer.
// For read-only access to stable strings (like definition names), it might be okay.
const char* safe_c_str(const std::string& str) {
    // Ensure string is not empty to avoid returning pointer to null terminator of empty string if underlying impl differs
    if (str.empty()) {
        return "";
    }
    return str.c_str();
}

// Placeholder for TextString conversion (from Subtask 2) - depends on its actual definition
const char* GetTextStringChar(const TextString& ts) {
    // Replace with actual implementation - guessing it has a GetText() or similar
    // return ts.GetText().c_str(); // Example
    return ""; // Placeholder - NEEDS ACTUAL IMPLEMENTATION
}


// Start of the single extern "C" block containing all implementations
extern "C" {

//======================================================================
// Implementations from Subtask 1: TemporalSystemWrapper, ShipSystemExtend
//======================================================================

// TemporalSystemWrapper Functions
bool TemporalSystemWrapper_IsReady(TemporalSystemWrapperPtr wrapper) {
    if (!wrapper) return false;
    TemporalSystem_Wrapper* cppWrapper = reinterpret_cast<TemporalSystem_Wrapper*>(wrapper);
    return cppWrapper->IsReady();
}

CTemporalArmState TemporalSystemWrapper_GetArmed(TemporalSystemWrapperPtr wrapper) {
    if (!wrapper) return C_TEMPORAL_ARM_NONE; // Return default/neutral state on null
    TemporalSystem_Wrapper* cppWrapper = reinterpret_cast<TemporalSystem_Wrapper*>(wrapper);
    return static_cast<CTemporalArmState>(cppWrapper->GetArmed());
}

int TemporalSystemWrapper_GetRealDilation(TemporalSystemWrapperPtr wrapper) {
    if (!wrapper) return 0;
    TemporalSystem_Wrapper* cppWrapper = reinterpret_cast<TemporalSystem_Wrapper*>(wrapper);
    return cppWrapper->GetRealDilation();
}

void TemporalSystemWrapper_SetArmed(TemporalSystemWrapperPtr wrapper, CTemporalArmState newArmState) {
    if (!wrapper) return;
    TemporalSystem_Wrapper* cppWrapper = reinterpret_cast<TemporalSystem_Wrapper*>(wrapper);
    cppWrapper->SetArmed(static_cast<TemporalArmState>(newArmState));
}

void TemporalSystemWrapper_StartTimeDilation(TemporalSystemWrapperPtr wrapper, int shipId, int roomId, bool speedUp) {
    if (!wrapper) return;
    TemporalSystem_Wrapper* cppWrapper = reinterpret_cast<TemporalSystem_Wrapper*>(wrapper);
    cppWrapper->StartTimeDilation(shipId, roomId, speedUp);
}

void TemporalSystemWrapper_StopTimeDilation(TemporalSystemWrapperPtr wrapper) {
    if (!wrapper) return;
    TemporalSystem_Wrapper* cppWrapper = reinterpret_cast<TemporalSystem_Wrapper*>(wrapper);
    cppWrapper->StopTimeDilation();
}

// ShipSystemExtend Functions
TemporalSystemWrapperPtr ShipSystemExtend_GetTemporalSystemWrapper(ShipSystemExtendPtr extend) {
    if (!extend) return nullptr;
    ShipSystem_Extend* cppExtend = reinterpret_cast<ShipSystem_Extend*>(extend);
    return reinterpret_cast<TemporalSystemWrapperPtr>(cppExtend->temporalSystem);
}

int ShipSystemExtend_GetAdditionalPowerLoss(ShipSystemExtendPtr extend) {
    if (!extend) return 0; // Return default value on null
    ShipSystem_Extend* cppExtend = reinterpret_cast<ShipSystem_Extend*>(extend);
    return cppExtend->additionalPowerLoss;
}

void ShipSystemExtend_SetAdditionalPowerLoss(ShipSystemExtendPtr extend, int loss) {
    if (!extend) return;
    ShipSystem_Extend* cppExtend = reinterpret_cast<ShipSystem_Extend*>(extend);
    cppExtend->additionalPowerLoss = loss;
}

int ShipSystemExtend_GetOverclockEffect(ShipSystemExtendPtr extend) {
    if (!extend) return 0; // Return default value on null
    ShipSystem_Extend* cppExtend = reinterpret_cast<ShipSystem_Extend*>(extend);
    return cppExtend->iOverclockEffect;
}

// Getter for the _Extend object (ShipSystem)
ShipSystemExtendPtr Get_ShipSystem_Extend_C(void* shipSystemPtr) {
    if (!shipSystemPtr) return nullptr;
    ShipSystem* cppSystem = reinterpret_cast<ShipSystem*>(shipSystemPtr);
    ShipSystem_Extend* cppExtend = Get_ShipSystem_Extend(cppSystem);
    return reinterpret_cast<ShipSystemExtendPtr>(cppExtend);
}


//============================================================================
// Implementations from Subtask 2: ProjectileExtend, CustomDamage, CustomWeapon
//============================================================================

// Helper to convert C++ CustomDamageDefinition* to opaque CCustomDamageDefinitionPtr
CCustomDamageDefinitionPtr WrapCustomDamageDefinition(CustomDamageDefinition* cppDef) {
     return reinterpret_cast<CCustomDamageDefinitionPtr>(cppDef);
}

// Helper to convert C++ CustomDamage to CCustomDamage
void ConvertCustomDamageToC(const CustomDamage& cppDamage, CCustomDamage* cDamage) {
    if (!cDamage) return;
    cDamage->definition = WrapCustomDamageDefinition(cppDamage.def);
    cDamage->sourceShipId = cppDamage.sourceShipId;
    // Note: accuracyMod and droneAccuracyMod are NOT part of cppDamage struct itself
}

// ProjectileExtend Functions
const char* ProjectileExtend_GetName(ProjectileExtendPtr extend) {
    if (!extend) return "";
    Projectile_Extend* cppExtend = reinterpret_cast<Projectile_Extend*>(extend);
    return safe_c_str(cppExtend->name);
}

void ProjectileExtend_GetCustomDamage(ProjectileExtendPtr extend, CCustomDamage* outDamage) {
    if (!extend || !outDamage) return;
    Projectile_Extend* cppExtend = reinterpret_cast<Projectile_Extend*>(extend);
    ConvertCustomDamageToC(cppExtend->customDamage, outDamage);
}

int ProjectileExtend_GetCustomDamageAccuracyMod(ProjectileExtendPtr extend) {
    if (!extend) return 0;
    Projectile_Extend* cppExtend = reinterpret_cast<Projectile_Extend*>(extend);
    return cppExtend->customDamage.accuracyMod;
}
void ProjectileExtend_SetCustomDamageAccuracyMod(ProjectileExtendPtr extend, int mod) {
    if (!extend) return;
    Projectile_Extend* cppExtend = reinterpret_cast<Projectile_Extend*>(extend);
    cppExtend->customDamage.accuracyMod = mod;
}
int ProjectileExtend_GetCustomDamageDroneAccuracyMod(ProjectileExtendPtr extend) {
    if (!extend) return 0;
    Projectile_Extend* cppExtend = reinterpret_cast<Projectile_Extend*>(extend);
    return cppExtend->customDamage.droneAccuracyMod;
}
void ProjectileExtend_SetCustomDamageDroneAccuracyMod(ProjectileExtendPtr extend, int mod) {
    if (!extend) return;
    Projectile_Extend* cppExtend = reinterpret_cast<Projectile_Extend*>(extend);
    cppExtend->customDamage.droneAccuracyMod = mod;
}

// Missed Drones (vector<int>) - Getter functions
int* ProjectileExtend_GetMissedDronesData(ProjectileExtendPtr extend) {
    if (!extend) return nullptr;
    Projectile_Extend* cppExtend = reinterpret_cast<Projectile_Extend*>(extend);
    // WARNING: Returning direct pointer is risky if vector reallocates.
    // Safer: provide functions to get size and element at index.
    return cppExtend->missedDrones.data(); // Use with caution!
}

size_t ProjectileExtend_GetMissedDronesSize(ProjectileExtendPtr extend) {
    if (!extend) return 0;
    Projectile_Extend* cppExtend = reinterpret_cast<Projectile_Extend*>(extend);
    return cppExtend->missedDrones.size();
}

// Getter for the _Extend object (Projectile)
ProjectileExtendPtr Get_Projectile_Extend_C(ProjectilePtr projectilePtr) {
    if (!projectilePtr) return nullptr;
    Projectile* cppProjectile = reinterpret_cast<Projectile*>(projectilePtr);
    Projectile_Extend* cppExtend = Get_Projectile_Extend(cppProjectile);
    return reinterpret_cast<ProjectileExtendPtr>(cppExtend);
}

// CustomDamageDefinition Functions (Accessing via CCustomDamageDefinitionPtr)
// Helper to safely get the C++ pointer
CustomDamageDefinition* UnwrapCustomDamageDefinition(CCustomDamageDefinitionPtr ptr) {
    return reinterpret_cast<CustomDamageDefinition*>(ptr);
}

int CustomDamageDefinition_GetIdx(CCustomDamageDefinitionPtr def) {
    CustomDamageDefinition* cppDef = UnwrapCustomDamageDefinition(def);
    return cppDef ? cppDef->idx : -1; // Return default/error value
}
int CustomDamageDefinition_GetAccuracyMod(CCustomDamageDefinitionPtr def) {
    CustomDamageDefinition* cppDef = UnwrapCustomDamageDefinition(def);
    return cppDef ? cppDef->accuracyMod : 0; // Return default/error value
}
// ... Implement other getters for CCustomDamageDefinition fields as needed ...


// CustomWeaponManager Functions

// Helper function (Conceptual - Implementation depends on TextString definition)
void ConvertTextStringToC(const TextString& cppTs, CTextString* cTs) {
    if (!cTs) return;
    // Replace with actual logic to get char* from TextString
    cTs->text = GetTextStringChar(cppTs); // Placeholder
}

// Helper to convert C++ CustomWeaponDefinition to CCustomWeaponDefinition
// WARNING: This implementation returns a pointer to a static cache.
// It is NOT thread-safe and subsequent calls overwrite the cache.
// Only suitable for simple, immediate use cases.
// A robust solution requires C# to allocate memory and C++ to fill it.
const CCustomWeaponDefinition* WrapCustomWeaponDefinition(const CustomWeaponDefinition* cppDef) {
    static thread_local CCustomWeaponDefinition c_def_cache; // Simple cache
    if (!cppDef) return nullptr;

    c_def_cache.name = safe_c_str(cppDef->name);
    c_def_cache.freeMissileChance = cppDef->freeMissileChance;
    ConvertTextStringToC(cppDef->descriptionOverride, &c_def_cache.descriptionOverride);
    // ... copy other simple fields ...
    c_def_cache.hideEventTooltip = cppDef->hideEventTooltip;
    c_def_cache.invisibleBeam = cppDef->invisibleBeam;
    c_def_cache.simultaneousFire = cppDef->simultaneousFire;
    c_def_cache.fireTime = cppDef->fireTime;
    c_def_cache.angularRadius = cppDef->angularRadius;
    c_def_cache.shotLimit = cppDef->shotLimit;
    c_def_cache.iconReplace = safe_c_str(cppDef->iconReplace);
    c_def_cache.iconScale = cppDef->iconScale;
    c_def_cache.customDamage = WrapCustomDamageDefinition(cppDef->customDamage);
    // Skip complex fields like maps for now

    return &c_def_cache;
}

const CCustomWeaponDefinition* CustomWeaponManager_GetWeaponDefinition(const char* bpName) {
    if (!bpName) return nullptr;
    // Ensure instance is initialized (Actual mechanism might differ)
    if (!CustomWeaponManager::instance) {
         // Handle error: Log or return null
         return nullptr;
    }
    CustomWeaponDefinition* cppDef = CustomWeaponManager::instance->GetWeaponDefinition(bpName);
    return WrapCustomWeaponDefinition(cppDef);
}

void CustomWeaponManager_ProcessMiniProjectile(ProjectilePtr projectilePtr, WeaponBlueprintPtr weaponBlueprintPtr, int boostLevel) {
    if (!projectilePtr || !weaponBlueprintPtr) return;
    Projectile* cppProjectile = reinterpret_cast<Projectile*>(projectilePtr);
    const WeaponBlueprint* cppWepBp = reinterpret_cast<const WeaponBlueprint*>(weaponBlueprintPtr);
    // Assuming CustomWeaponManager::ProcessMiniProjectile is static
    CustomWeaponManager::ProcessMiniProjectile(cppProjectile, cppWepBp, boostLevel);
}


//==========================================================================
// Implementations from Subtask 3: CustomDroneManager, SaveFileHandler
//==========================================================================

// Assume CustomDroneManager::GetInstance() and SaveFileHandler::instance are accessible

// Helper to get SaveFileHandler instance (assuming static instance member)
SaveFileHandler* GetSaveFileHandlerInstance() {
    // Replace with actual access if ::instance is not public/static
    // e.g., if SaveFileHandler has a static GetInstance method:
    // return SaveFileHandler::GetInstance();
    // Assuming public static instance for now:
    return SaveFileHandler::instance;
}

// Helper to get CustomDroneManager instance (using GetInstance())
CustomDroneManager* GetCustomDroneManagerInstance() {
    // This assumes GetInstance() is public static as seen in the header
    return CustomDroneManager::GetInstance();
}

// Helper function to convert C++ DroneAbilityDefinition to C struct
void ConvertDroneAbilityDefinitionToC(const DroneAbilityDefinition& cppDef, CDroneAbilityDefinition* cDef) {
    if (!cDef) return;
    cDef->delay = cppDef.delay;
    // Map enum class value
    switch (cppDef.ai) {
        case DroneAbilityDefinition::AIType::SYSTEMS:        cDef->ai = C_DRONE_AI_SYSTEMS; break;
        case DroneAbilityDefinition::AIType::SYSTEMS_POWER:  cDef->ai = C_DRONE_AI_SYSTEMS_POWER; break;
        case DroneAbilityDefinition::AIType::CREW_HEAL:      cDef->ai = C_DRONE_AI_CREW_HEAL; break;
        case DroneAbilityDefinition::AIType::ENEMIES:        cDef->ai = C_DRONE_AI_ENEMIES; break;
        default:                                             cDef->ai = C_DRONE_AI_SYSTEMS; // Default case
    }
}

// Helper function to convert C++ CustomDroneDefinition to C struct
// WARNING: Uses static cache - not thread-safe, subsequent calls overwrite.
const CCustomDroneDefinition* WrapCustomDroneDefinition(const CustomDroneDefinition* cppDef) {
    // Using thread_local for minimal safety in multi-threaded C# callers,
    // but still unsafe if C# code stores the pointer across calls.
    static thread_local CCustomDroneDefinition c_def_cache;
    if (!cppDef) return nullptr;

    c_def_cache.name = safe_c_str(cppDef->name);
    c_def_cache.tooltipName = safe_c_str(cppDef->tooltipName);
    c_def_cache.crewBlueprint = safe_c_str(cppDef->crewBlueprint);
    c_def_cache.hasAbility = cppDef->hasAbility;
    ConvertDroneAbilityDefinitionToC(cppDef->ability, &c_def_cache.ability);

    return &c_def_cache;
}


// CustomDroneManager Functions
const CCustomDroneDefinition* CustomDroneManager_GetDefinition(const char* droneName) {
    if (!droneName) return nullptr;
    CustomDroneManager* manager = GetCustomDroneManagerInstance();
    if (!manager) return nullptr; // Handle manager not found
    CustomDroneDefinition* cppDef = manager->GetDefinition(droneName);
    return WrapCustomDroneDefinition(cppDef);
}

const CCustomDroneDefinition* CustomDroneManager_GetDefinitionByRace(const char* raceName) {
    if (!raceName) return nullptr;
    CustomDroneManager* manager = GetCustomDroneManagerInstance();
    if (!manager) return nullptr;
    CustomDroneDefinition* cppDef = manager->GetDefinitionByRace(raceName);
    return WrapCustomDroneDefinition(cppDef);
}

// SaveFileHandler Functions
void SaveFileHandler_CreateTransferFile() {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    if (handler) {
        handler->CreateTransferFile();
    }
    // Else: Log error or do nothing if handler is not available
}

void SaveFileHandler_DeleteTransferFile() {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    if (handler) {
        handler->DeleteTransferFile();
    }
}

bool SaveFileHandler_TransferFileExists() {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    return handler ? handler->TransferFileExists() : false;
}

const char* SaveFileHandler_GetSavePrefix() {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    // Potential lifetime issue if prefix changes. Copy to C# buffer is safer.
    return handler ? safe_c_str(handler->savePrefix) : "";
}

void SaveFileHandler_SetSavePrefix(const char* prefix) {
    if (!prefix) return; // Don't set null prefix
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    if (handler) {
        handler->savePrefix = prefix; // Assign C string to std::string
    }
}

bool SaveFileHandler_GetFirstTime() {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    return handler ? handler->firstTime : false; // Default value if handler null
}

void SaveFileHandler_SetFirstTime(bool value) {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    if (handler) {
        handler->firstTime = value;
    }
}

bool SaveFileHandler_GetWelcomeDialog() {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    return handler ? handler->welcomeDialog : false;
}

void SaveFileHandler_SetWelcomeDialog(bool value) {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    if (handler) {
        handler->welcomeDialog = value;
    }
}

CInheritMode SaveFileHandler_GetInheritMode() {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    if (!handler) return C_INHERIT_MODE_FORCE_OLD; // Default
    // Map enum class value
    switch (handler->inheritMode) {
        case SaveFileHandler::InheritMode::FORCE_OLD:   return C_INHERIT_MODE_FORCE_OLD;
        case SaveFileHandler::InheritMode::ASK_PLAYER:  return C_INHERIT_MODE_ASK_PLAYER;
        case SaveFileHandler::InheritMode::FORCE_NEW:   return C_INHERIT_MODE_FORCE_NEW;
        default:                                        return C_INHERIT_MODE_FORCE_OLD;
    }
}

void SaveFileHandler_SetInheritMode(CInheritMode mode) {
    SaveFileHandler* handler = GetSaveFileHandlerInstance();
    if (!handler) return;
    // Map C enum value to C++ enum class
    SaveFileHandler::InheritMode cppMode;
    switch (mode) {
        case C_INHERIT_MODE_FORCE_OLD:   cppMode = SaveFileHandler::InheritMode::FORCE_OLD; break;
        case C_INHERIT_MODE_ASK_PLAYER:  cppMode = SaveFileHandler::InheritMode::ASK_PLAYER; break;
        case C_INHERIT_MODE_FORCE_NEW:   cppMode = SaveFileHandler::InheritMode::FORCE_NEW; break;
        default:                         cppMode = SaveFileHandler::InheritMode::FORCE_OLD; // Default
    }
    handler->inheritMode = cppMode;
}


} // End of the single extern "C" block
