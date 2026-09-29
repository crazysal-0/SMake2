#pragma once

#include <lua.h>

void smake_register_api(lua_State* L);
int smake_target_executable(lua_State* L);