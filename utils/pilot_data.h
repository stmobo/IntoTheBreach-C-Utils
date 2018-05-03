#pragma once

typedef void* PilotData;

/* Offsets into the pilot data structure */
#define PILOT_NAME_OFFSET 0x20
#define PILOT_CUR_EXP_OFFSET 0x3C
#define PILOT_LEVELUP_EXP_OFFSET 0x40
#define PILOT_ABILITY_OFFSET 0x6C
#define PILOT_ID_OFFSET 0x84
#define PILOT_LEVEL_OFFSET 0x68
#define PILOT_PERSONALITY_OFFSET 0xA0
#define PILOT_VOICE_OFFSET 0x250

/* Offset of pointer to pilot struct within Pawn struct */
#define PILOT_PTR_OFFSET 0x944

PilotData getPilotData(void * pawn);

int getPilotEXP(PilotData p);
void setPilotEXP(PilotData p, int exp);

int getPilotLevelUpEXP(PilotData p);
void setPilotLevelUpEXP(PilotData p, int exp);

int getPilotLevel(PilotData p);
void setPilotLevel(PilotData p, int lvl);

char * getPilotName(PilotData p);
char * getPilotAbility(PilotData p);
char * getPilotID(PilotData p);
char * getPilotPersonality(PilotData p);
char * getPilotVoice(PilotData p);
