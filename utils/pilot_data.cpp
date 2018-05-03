#include "stdafx.h"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include "pilot_data.h"

int peek_offset(PilotData p, int offset) {
	return *(int*)((uintptr_t)p + offset);
}

void poke_offset(PilotData p, int offset, int value) {
	int* ptr = (int*)((uintptr_t)p + offset);
	*ptr = value;
}

char* string_offset(PilotData p, int offset) {
	return (char*)((uintptr_t)p + offset);
}


PilotData getPilotData(void* pawn) {
	return *(PilotData*)((uintptr_t)pawn + PILOT_PTR_OFFSET);
}

int getPilotEXP(PilotData p) {
	return peek_offset(p, PILOT_CUR_EXP_OFFSET);
}

void setPilotEXP(PilotData p, int exp) {
	return poke_offset(p, PILOT_CUR_EXP_OFFSET, exp);
}

int getPilotLevelUpEXP(PilotData p) {
	return peek_offset(p, PILOT_LEVELUP_EXP_OFFSET);
}

void setPilotLevelUpEXP(PilotData p, int exp) {
	return poke_offset(p, PILOT_LEVELUP_EXP_OFFSET, exp);
}

int getPilotLevel(PilotData p) {
	return peek_offset(p, PILOT_LEVEL_OFFSET);
}

void setPilotLevel(PilotData p, int lvl) {
	return poke_offset(p, PILOT_LEVEL_OFFSET, lvl);
}

char* getPilotName(PilotData p) {
	return string_offset(p, PILOT_NAME_OFFSET);
}

char* getPilotAbility(PilotData p) {
	return string_offset(p, PILOT_ABILITY_OFFSET);
}

char* getPilotID(PilotData p) {
	return string_offset(p, PILOT_ID_OFFSET);
}

char* getPilotPersonality(PilotData p) {
	return string_offset(p, PILOT_PERSONALITY_OFFSET);
}

/* skill 0 = mech hp
 * skill 1 = mech move
 * skill 2 = grid def
 * skill 3 = mech reactor
 */

char* getPilotVoice(PilotData p) {
	return string_offset(p, PILOT_VOICE_OFFSET);
}