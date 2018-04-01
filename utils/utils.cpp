// utils.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "lua.hpp"

#include <cstdint>
#include <string>
#include <vector>

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
struct Weapon {
	void* head;
	void* tail;
};
int getweaponname(lua_State* L) {
	void* weapon_vec_addr = (int*)get_pawn(L, 1)+1;

	size_t idx = luaL_checkint(L, 2);

	std::vector<Weapon>* weapon_vector = static_cast<std::vector<Weapon>*>(weapon_vec_addr);

	if (idx >= weapon_vector->size()) {
		lua_pushnil(L);
		return 1;
	}
	void* weapon_addr = (*weapon_vector)[idx].tail;
	void* string_addr = (void*)((int)weapon_addr + 0xc0);

	std::basic_string<char>* name = static_cast<std::basic_string<char>*>(string_addr);
	lua_pushstring(L, name->c_str());
	return 1;
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

void* offset(void* base, size_t delta) {
	return (void*)((int)base + delta);
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

static const struct luaL_Reg Utils[] = {
{ "GetWeaponName", getweaponname },
{ "GetPawnAddr", getpawnaddr },
{ "SetHealth", set_health},
{ "SetMaxHealth", set_max_health },
{ "GetMaxHealth", get_max_health },
{ "GetTileHealth", get_tile_health },

{ NULL,           NULL } };
extern "C" {
	int  __declspec(dllexport) luaopen_utils(lua_State* L) {
		luaL_register(L, "test", Utils);
		return 1;
	}
}