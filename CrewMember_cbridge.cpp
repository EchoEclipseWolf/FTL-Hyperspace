#include "CrewMember_cbridge.h"
#include "FTLGameWin32.h" // Assuming this header contains the definition for CrewMember and ShipSystem
#include "CrewMember_Extend.h" // Assuming this header contains the definition for CrewMember_Extend and the function Get_CrewMember_Extend
#include <string>
#include <vector> // Include vector if CrewMember::GetName() returns std::vector<char> or similar
#include <cstring> // For strncpy

extern "C" {

struct Point HS_CrewMember_GetPosition(CrewMember* self) {
    // Assuming CrewMember::GetPosition() returns a Point struct or similar
    // and that the C Point and C++ Point are compatible or conversion is handled here.
    Point p = self->GetPosition();
    return p;
}

bool HS_CrewMember_InsideRoom(CrewMember* self, int roomId) {
    return self->InsideRoom(roomId);
}

void HS_CrewMember_SetCurrentSystem(CrewMember* self, ShipSystem* sys) {
    self->SetCurrentSystem(sys);
}

void HS_CrewMember_GetName(CrewMember* self, char* buffer, int bufferSize) {
    // Assuming CrewMember::GetName() returns a type convertible to C-string, like std::string
    // Need to know the exact return type of GetName() to be sure.
    // If GetName returns std::string:
    std::string name = self->GetName();
    strncpy(buffer, name.c_str(), bufferSize - 1);
    buffer[bufferSize - 1] = '\0'; // Ensure null termination

    // If GetName returns something else, adjust accordingly.
    // For example, if it returns a const char*:
    // const char* name = self->GetName();
    // strncpy(buffer, name, bufferSize - 1);
    // buffer[bufferSize - 1] = '\0'; // Ensure null termination
}

int HS_CrewMember_GetSkillFromSystem(int systemId) {
    // Assuming CrewMember::GetSkillFromSystem is a static method
    return CrewMember::GetSkillFromSystem(systemId);
}

struct CrewMember_Extend* HS_Get_CrewMember_Extend(const CrewMember* c) {
    // Assuming Get_CrewMember_Extend is a function available in CrewMember_Extend.h
    return Get_CrewMember_Extend(c);
}

} // extern "C"
