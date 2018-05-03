// utils.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "lua.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include "pilot_data.h"

void* offset(void* base, size_t delta) {
	return (void*)((int)base + delta);
}

void* get_data(lua_State* L, const char* error, int idx) {
	void*** userdata = (void***)lua_touserdata(L, idx);
	luaL_argcheck(L, userdata != NULL, 1, error);
	return userdata[0][2];
}

void* get_pawn(lua_State* L, int idx) {
	return get_data(L, "`pawn' expected", idx);
}

int getpawnaddr(lua_State* L) {
	void* pawn = get_pawn(L, 1);
	lua_pushinteger(L, (int)pawn);
	return 1;
}

typedef std::shared_ptr<void*> Weapon;

std::vector<Weapon>* weapon_vec(void* pawn) {
	void* weapon_vec_addr = (int*)pawn+1;
	std::vector<Weapon>* weapon_vector = static_cast<std::vector<Weapon>*>(weapon_vec_addr);
	return weapon_vector;
}

Weapon* weapon_at(void* pawn, size_t idx) {
	if (idx == 50) {
		return (Weapon*)offset(pawn, 0x5c);
	} else {
		std::vector<Weapon>* weapon_vector = weapon_vec(pawn);
		if (idx < 0 || weapon_vector->size() <= idx) {
			return NULL;
		}
		return &(*weapon_vector)[idx];
	}
}

int getweaponname(lua_State* L) {
	void* pawn = get_pawn(L, 1);
	size_t idx = luaL_checkint(L, 2);


	Weapon* weapon = weapon_at(pawn, idx);

	if (weapon == NULL) {
		lua_pushnil(L);
		return 1;
	}
	void* string_addr = (void*)((int)weapon->get() + 0xb4);

	std::basic_string<char>* name = static_cast<std::basic_string<char>*>(string_addr);
	lua_pushstring(L, name->c_str());
	return 1;
}

int replace_weapon(lua_State*L) {
	void* pawn = (int*)get_pawn(L, 1);
	size_t new_idx = luaL_checkint(L, 2);

	std::vector<Weapon>* weapons = weapon_vec(pawn);
	Weapon& w = weapons->back();

	Weapon& o = *weapon_at(pawn, new_idx);
	w.swap(o);

	weapons->pop_back();
	return 0;
}

int* get_pawn_data_at(void* pawn, int offset) {
	return (int*)((int)pawn + 0x86c + offset);
}

int set_health(lua_State* L) {
	int* pawn_health = get_pawn_data_at(get_pawn(L, 1), 4);
	int new_val = luaL_checkint(L, 2);
	*pawn_health = new_val;
	return 0;
}

int set_max_health(lua_State* L) {
	int* pawn_max_health = get_pawn_data_at(get_pawn(L, 1), 8);
	int new_val = luaL_checkint(L, 2);
	*pawn_max_health = new_val;
	return 0;
}

int get_max_health(lua_State* L) {
	int* pawn_max_health = get_pawn_data_at(get_pawn(L, 1), 8);
	lua_pushinteger(L, *pawn_max_health);
	return 1;
}


int get_tile_health(lua_State* L) {
	void* board = get_data(L, "`board' expected", 1);
	int x = luaL_checkint(L, 2);
	int y = luaL_checkint(L, 3);

	void* row_vec = *(void**)offset(board, 0x4c);
	void* column_arr = *(void**)offset(row_vec, 12 * x);
	void* tile = offset(column_arr, 0x21f0 * y);
	void* tile_health = offset(tile, 0x6c);

	lua_pushinteger(L, *(int*)tile_health);
	return 1;
}

int get_pilot_data_ref(lua_State* L) {
	void* pawn = get_pawn(L, 1);
	PilotData p = getPilotData(pawn);

	lua_pushinteger(L, (int)p);
	return 1;
}

int get_pilot_exp(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	lua_pushinteger(L, getPilotEXP(p));

	return 1;
}

int set_pilot_exp(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	setPilotEXP(p, luaL_checkint(L, 2));
	return 0;
}

int get_pilot_levelup_exp(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	lua_pushinteger(L, getPilotLevelUpEXP(p));

	return 1;
}

int set_pilot_levelup_exp(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	setPilotLevelUpEXP(p, luaL_checkint(L, 2));
	return 0;
}

int get_pilot_level(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	lua_pushinteger(L, getPilotLevel(p));

	return 1;
}

int set_pilot_level(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	setPilotLevel(p, luaL_checkint(L, 2));
	return 0;
}


int get_pilot_name(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	lua_pushlstring(L, getPilotName(p), 16);

	return 1;
}

int set_pilot_name(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);
	size_t name_len = 0;
	const char* new_name = luaL_checklstring(L, 2, &name_len);

	if (name_len > 16) {
		return luaL_argerror(L, 2, "name must be <= 16 characters");
	}

	char* name_ptr = getPilotName(p);
	strncpy(name_ptr, new_name, 16);

	return 0;
}

int get_pilot_ability(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	lua_pushlstring(L, getPilotAbility(p), 16);

	return 1;
}

int set_pilot_ability(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);
	size_t ab_len = 0;
	const char* new_ability = luaL_checklstring(L, 2, &ab_len);

	if (ab_len > 16) {
		return luaL_argerror(L, 2, "id must be <= 16 characters");
	}

	char* ab_ptr = getPilotAbility(p);
	strncpy(ab_ptr, new_ability, 16);

	return 0;
}

int get_pilot_id(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	lua_pushlstring(L, getPilotID(p), 16);

	return 1;
}

int set_pilot_id(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);
	size_t id_len = 0;
	const char* new_id = luaL_checklstring(L, 2, &id_len);

	if (id_len > 16) {
		return luaL_argerror(L, 2, "id must be <= 16 characters");
	}

	char* id_ptr = getPilotID(p);
	strncpy(id_ptr, new_id, 16);

	return 0;
}

int get_pilot_personality(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);

	lua_pushlstring(L, getPilotID(p), 16);

	return 1;
}

int set_pilot_personality(lua_State* L) {
	PilotData p = (PilotData)luaL_checkint(L, 1);
	size_t pers_len = 0;
	const char* new_pers = luaL_checklstring(L, 2, &pers_len);

	if (pers_len > 16) {
		return luaL_argerror(L, 2, "id must be <= 16 characters");
	}

	char* pers_ptr = getPilotPersonality(p);
	strncpy(pers_ptr, new_pers, 16);

	return 0;
}


static const struct luaL_Reg Utils[] = {
{ "GetWeaponName", getweaponname },
{ "GetPawnAddr", getpawnaddr },
{ "SetHealth", set_health},
{ "SetMaxHealth", set_max_health },
{ "GetMaxHealth", get_max_health },
{ "GetTileHealth", get_tile_health },
{ "ReplaceWeapon", replace_weapon },

{ "GetPilotAddr", get_pilot_data_ref },

{ "GetPilotEXP", get_pilot_exp },
{ "SetPilotEXP", set_pilot_exp },

{ "GetPilotLevelUpEXP", get_pilot_levelup_exp },
{ "SetPilotLevelUpEXP", set_pilot_levelup_exp },

{ "GetPilotLevel", get_pilot_level },
{ "SetPilotLevel", set_pilot_level },

{ "GetPilotName", get_pilot_name },
{ "SetPilotName", set_pilot_name },

{ "GetPilotAbility", get_pilot_ability },
{ "SetPilotAbility", set_pilot_ability },

{ "GetPilotPersonality", get_pilot_personality },
{ "SetPilotPersonality", set_pilot_personality },

{ "GetPilotID", get_pilot_id },
{ "SetPilotID", set_pilot_id },
{ NULL,           NULL } };

extern "C" {
	int  __declspec(dllexport) luaopen_utils(lua_State* L) {
		luaL_register(L, "test", Utils);
		return 1;
	}
}
