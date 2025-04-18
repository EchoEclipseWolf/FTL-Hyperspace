#pragma once

#include <stdint.h>

// Forward declarations
struct CrewMember;
struct ShipSystem;
struct Point;
struct CrewMember_Extend;

#ifdef __cplusplus
extern "C" {
#endif

// Define a C-compatible Point struct
struct Point {
    int x;
    int y;
};

struct Point HS_CrewMember_GetPosition(CrewMember* self);
bool HS_CrewMember_InsideRoom(CrewMember* self, int roomId);
void HS_CrewMember_SetCurrentSystem(CrewMember* self, ShipSystem* sys);
void HS_CrewMember_GetName(CrewMember* self, char* buffer, int bufferSize);
int HS_CrewMember_GetSkillFromSystem(int systemId);
struct CrewMember_Extend* HS_Get_CrewMember_Extend(const CrewMember* c);


#ifdef __cplusplus
}
#endif
