using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Hyperspace.NetBindings
{
    [StructLayout(LayoutKind.Sequential)]
    public struct CsPoint
    {
        public int x;
        public int y;
    }

    public static class CrewMemberBindings
    {
        private const string DllName = "Hyperspace";

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern CsPoint HS_CrewMember_GetPosition(IntPtr self);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)] // Explicitly marshal bool as 1 byte
        public static extern bool HS_CrewMember_InsideRoom(IntPtr self, int roomId);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void HS_CrewMember_SetCurrentSystem(IntPtr self, IntPtr sys);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void HS_CrewMember_GetName(IntPtr self, StringBuilder buffer, int bufferSize);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int HS_CrewMember_GetSkillFromSystem(int systemId);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr HS_Get_CrewMember_Extend(IntPtr c);
    }
}
