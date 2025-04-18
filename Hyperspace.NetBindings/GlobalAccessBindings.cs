using System;
using System.Runtime.InteropServices;

namespace Hyperspace.NetBindings
{
    public static class GlobalAccessBindings
    {
        private const string DllName = "Hyperspace";

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr HS_Global_GetResources();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr HS_Global_GetCApp();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr HS_Global_GetWorld();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr HS_Global_GetBlueprints();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr HS_Global_GetCrewFactory();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr HS_Global_GetSettings();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int HS_Globals_GetNextSpaceId();

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool HS_FileHelper_fileExists([MarshalAs(UnmanagedType.LPStr)] string fileName);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool HS_Settings_GetDlcEnabled();
    }
}
