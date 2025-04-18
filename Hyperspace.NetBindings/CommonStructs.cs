using System;
using System.Runtime.InteropServices;

namespace Hyperspace.NetBindings;

// --- Enums ---
public enum CTemporalArmState
{
    None = 0,
    Speed = 1,
    Slow = 2
}

public enum CDroneAbilityAIType
{
    Systems,
    SystemsPower,
    CrewHeal,
    Enemies
}

public enum CInheritMode
{
    ForceOld,
    AskPlayer,
    ForceNew
}

// --- Structs ---
// Note: Using IntPtr for char* fields within structs returned by pointer
// due to marshalling complexity/lifetime issues. Use Marshal.PtrToStringAnsi/Utf8.

[StructLayout(LayoutKind.Sequential)]
public struct CTextString // Simplified assumption - Layout needs verification
{
    public IntPtr text; // const char*
}

[StructLayout(LayoutKind.Sequential)]
public struct CCustomDamageDefinition // Simplified
{
    public int idx;
    public int accuracyMod;
    public int droneAccuracyMod;
    [MarshalAs(UnmanagedType.I1)] // Explicitly marshal bool as 1 byte
    public bool noSysDamage;
    [MarshalAs(UnmanagedType.I1)]
    public bool noPersDamage;
    // Skipping vectors and complex types
}

[StructLayout(LayoutKind.Sequential)]
public struct CCustomDamage
{
    public IntPtr definition; // CCustomDamageDefinitionPtr -> Treat as IntPtr
    public int sourceShipId;
}

[StructLayout(LayoutKind.Sequential)]
public struct CCustomWeaponDefinition // Simplified
{
    public IntPtr name; // const char*
    public int freeMissileChance;
    public CTextString descriptionOverride; // Assumes CTextString layout is correct
    [MarshalAs(UnmanagedType.I1)]
    public bool hideEventTooltip;
    [MarshalAs(UnmanagedType.I1)]
    public bool invisibleBeam;
    [MarshalAs(UnmanagedType.I1)]
    public bool simultaneousFire;
    public float fireTime;
    public float angularRadius;
    public int shotLimit;
    public IntPtr iconReplace; // const char*
    public float iconScale;
    public IntPtr customDamage; // CCustomDamageDefinitionPtr
    // Skipping map
}

[StructLayout(LayoutKind.Sequential)]
public struct CDroneAbilityDefinition
{
    public int delay;
    public CDroneAbilityAIType ai;
}

[StructLayout(LayoutKind.Sequential)]
public struct CCustomDroneDefinition
{
    public IntPtr name; // const char*
    public IntPtr tooltipName; // const char*
    public IntPtr crewBlueprint; // const char*
    [MarshalAs(UnmanagedType.I1)]
    public bool hasAbility;
    public CDroneAbilityDefinition ability;
}

// Note: Opaque pointers like TemporalSystemWrapperPtr, ShipSystemExtendPtr, etc.
// are represented directly as IntPtr in the NativeMethods signatures.
