// utils.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "lua.hpp"

#include <cstdint>
#include <string>
#include <vector>

int getpawnaddr(lua_State* L) {
	int* outer = *(int**)lua_touserdata(L, 1);
	int inner = outer[2];
	lua_pushinteger(L, inner);
	return 1;
}
struct Weapon {
	void* head;
	void* tail;
};
int getweaponname(lua_State* L) {
	int*** userdata = (int***)lua_touserdata(L, 1);
	size_t idx = luaL_checkint(L, 2);
	luaL_argcheck(L, userdata != NULL, 1, "`pawn' expected");

	// we go userdata -> luabind data -> pawn struct
	void* weapon_vec_addr = &userdata[0][2][1];

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
static const struct luaL_Reg Utils[] = { { "GetWeaponName", getweaponname },
{ "GetPawnAddr", getpawnaddr },
{ NULL,           NULL } };
extern "C" {
	int  __declspec(dllexport) luaopen_utils(lua_State* L) {
		luaL_register(L, "test", Utils);
		return 1;
	}
}