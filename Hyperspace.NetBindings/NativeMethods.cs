using System;
using System.Runtime.InteropServices;
using System.Text; // For potential StringBuilder usage

namespace Hyperspace.NetBindings;

// Using internal static partial class allows splitting native methods across files if needed later.
internal static partial class NativeMethods
{
    // TODO: Adjust library name based on actual compiled output (DLL/SO)
    // Ensure this library is accessible to the C# application (e.g., in the same directory or PATH).
    private const string LibName = "HyperspaceBridge"; // Example name

    // --- TemporalSystemWrapper Functions ---
    [LibraryImport(LibName, EntryPoint = "TemporalSystemWrapper_IsReady")]
    [return: MarshalAs(UnmanagedType.Bool)] // Use Bool for clarity over I1 if preferred
    internal static partial bool TemporalSystemWrapper_IsReady(IntPtr wrapper); // TemporalSystemWrapperPtr

    [LibraryImport(LibName, EntryPoint = "TemporalSystemWrapper_GetArmed")]
    internal static partial CTemporalArmState TemporalSystemWrapper_GetArmed(IntPtr wrapper); // TemporalSystemWrapperPtr

    [LibraryImport(LibName, EntryPoint = "TemporalSystemWrapper_GetRealDilation")]
    internal static partial int TemporalSystemWrapper_GetRealDilation(IntPtr wrapper); // TemporalSystemWrapperPtr

    [LibraryImport(LibName, EntryPoint = "TemporalSystemWrapper_SetArmed")]
    internal static partial void TemporalSystemWrapper_SetArmed(IntPtr wrapper, CTemporalArmState newArmState); // TemporalSystemWrapperPtr

    [LibraryImport(LibName, EntryPoint = "TemporalSystemWrapper_StartTimeDilation")]
    internal static partial void TemporalSystemWrapper_StartTimeDilation(IntPtr wrapper, int shipId, int roomId, [MarshalAs(UnmanagedType.Bool)] bool speedUp); // TemporalSystemWrapperPtr

    [LibraryImport(LibName, EntryPoint = "TemporalSystemWrapper_StopTimeDilation")]
    internal static partial void TemporalSystemWrapper_StopTimeDilation(IntPtr wrapper); // TemporalSystemWrapperPtr

    // --- ShipSystemExtend Functions ---
    [LibraryImport(LibName, EntryPoint = "ShipSystemExtend_GetTemporalSystemWrapper")]
    internal static partial IntPtr ShipSystemExtend_GetTemporalSystemWrapper(IntPtr extend); // ShipSystemExtendPtr -> TemporalSystemWrapperPtr

    [LibraryImport(LibName, EntryPoint = "ShipSystemExtend_GetAdditionalPowerLoss")]
    internal static partial int ShipSystemExtend_GetAdditionalPowerLoss(IntPtr extend); // ShipSystemExtendPtr

    [LibraryImport(LibName, EntryPoint = "ShipSystemExtend_SetAdditionalPowerLoss")]
    internal static partial void ShipSystemExtend_SetAdditionalPowerLoss(IntPtr extend, int loss); // ShipSystemExtendPtr

    [LibraryImport(LibName, EntryPoint = "ShipSystemExtend_GetOverclockEffect")]
    internal static partial int ShipSystemExtend_GetOverclockEffect(IntPtr extend); // ShipSystemExtendPtr

    [LibraryImport(LibName, EntryPoint = "Get_ShipSystem_Extend_C")]
    internal static partial IntPtr Get_ShipSystem_Extend_C(IntPtr shipSystemPtr); // void* -> ShipSystemExtendPtr

    // --- ProjectileExtend Functions ---
    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_GetName", StringMarshalling = StringMarshalling.Utf8)] // Assuming UTF8 strings from C++
    internal static partial string ProjectileExtend_GetName_MARSHALLED(IntPtr extend); // Use alternative entry point if direct IntPtr needed

    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_GetName")]
    internal static partial IntPtr ProjectileExtend_GetName(IntPtr extend); // ProjectileExtendPtr -> const char* (IntPtr for manual marshalling)

    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_GetCustomDamage")]
    internal static partial void ProjectileExtend_GetCustomDamage(IntPtr extend, out CCustomDamage outDamage); // ProjectileExtendPtr

    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_GetCustomDamageAccuracyMod")]
    internal static partial int ProjectileExtend_GetCustomDamageAccuracyMod(IntPtr extend); // ProjectileExtendPtr

    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_SetCustomDamageAccuracyMod")]
    internal static partial void ProjectileExtend_SetCustomDamageAccuracyMod(IntPtr extend, int mod); // ProjectileExtendPtr

    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_GetCustomDamageDroneAccuracyMod")]
    internal static partial int ProjectileExtend_GetCustomDamageDroneAccuracyMod(IntPtr extend); // ProjectileExtendPtr

    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_SetCustomDamageDroneAccuracyMod")]
    internal static partial void ProjectileExtend_SetCustomDamageDroneAccuracyMod(IntPtr extend, int mod); // ProjectileExtendPtr

    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_GetMissedDronesData")]
    internal static partial IntPtr ProjectileExtend_GetMissedDronesData(IntPtr extend); // ProjectileExtendPtr -> int* (IntPtr)

    [LibraryImport(LibName, EntryPoint = "ProjectileExtend_GetMissedDronesSize")]
    internal static partial nuint ProjectileExtend_GetMissedDronesSize(IntPtr extend); // ProjectileExtendPtr -> size_t (nuint)

    [LibraryImport(LibName, EntryPoint = "Get_Projectile_Extend_C")]
    internal static partial IntPtr Get_Projectile_Extend_C(IntPtr projectilePtr); // ProjectilePtr -> ProjectileExtendPtr

    // --- CustomDamageDefinition Functions ---
    [LibraryImport(LibName, EntryPoint = "CustomDamageDefinition_GetIdx")]
    internal static partial int CustomDamageDefinition_GetIdx(IntPtr def); // CCustomDamageDefinitionPtr

    [LibraryImport(LibName, EntryPoint = "CustomDamageDefinition_GetAccuracyMod")]
    internal static partial int CustomDamageDefinition_GetAccuracyMod(IntPtr def); // CCustomDamageDefinitionPtr

    // --- CustomWeaponManager Functions ---
    // Returns IntPtr to the cached C struct. Caller Marshals manually.
    [LibraryImport(LibName, EntryPoint = "CustomWeaponManager_GetWeaponDefinition")]
    internal static partial IntPtr CustomWeaponManager_GetWeaponDefinition([MarshalAs(UnmanagedType.LPStr)] string bpName); // const char* -> CCustomWeaponDefinition* (IntPtr)

    [LibraryImport(LibName, EntryPoint = "CustomWeaponManager_ProcessMiniProjectile")]
    internal static partial void CustomWeaponManager_ProcessMiniProjectile(IntPtr projectilePtr, IntPtr weaponBlueprintPtr, int boostLevel); // ProjectilePtr, WeaponBlueprintPtr

    // --- CustomDroneManager Functions ---
    // Returns IntPtr to the cached C struct. Caller Marshals manually.
    [LibraryImport(LibName, EntryPoint = "CustomDroneManager_GetDefinition")]
    internal static partial IntPtr CustomDroneManager_GetDefinition([MarshalAs(UnmanagedType.LPStr)] string droneName); // const char* -> CCustomDroneDefinition* (IntPtr)

    // Returns IntPtr to the cached C struct. Caller Marshals manually.
    [LibraryImport(LibName, EntryPoint = "CustomDroneManager_GetDefinitionByRace")]
    internal static partial IntPtr CustomDroneManager_GetDefinitionByRace([MarshalAs(UnmanagedType.LPStr)] string raceName); // const char* -> CCustomDroneDefinition* (IntPtr)

    // --- SaveFileHandler Functions ---
    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_CreateTransferFile")]
    internal static partial void SaveFileHandler_CreateTransferFile();

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_DeleteTransferFile")]
    internal static partial void SaveFileHandler_DeleteTransferFile();

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_TransferFileExists")]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static partial bool SaveFileHandler_TransferFileExists();

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_GetSavePrefix")]
    internal static partial IntPtr SaveFileHandler_GetSavePrefix(); // const char* (IntPtr for manual marshalling)

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_SetSavePrefix")]
    internal static partial void SaveFileHandler_SetSavePrefix([MarshalAs(UnmanagedType.LPStr)] string prefix); // const char*

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_GetFirstTime")]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static partial bool SaveFileHandler_GetFirstTime();

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_SetFirstTime")]
    internal static partial void SaveFileHandler_SetFirstTime([MarshalAs(UnmanagedType.Bool)] bool value);

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_GetWelcomeDialog")]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static partial bool SaveFileHandler_GetWelcomeDialog();

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_SetWelcomeDialog")]
    internal static partial void SaveFileHandler_SetWelcomeDialog([MarshalAs(UnmanagedType.Bool)] bool value);

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_GetInheritMode")]
    internal static partial CInheritMode SaveFileHandler_GetInheritMode();

    [LibraryImport(LibName, EntryPoint = "SaveFileHandler_SetInheritMode")]
    internal static partial void SaveFileHandler_SetInheritMode(CInheritMode mode);
}
