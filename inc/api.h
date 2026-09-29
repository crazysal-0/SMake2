#pragma once

#include <lua.h>

int smake_run_cmd(lua_State* L);
int smake_target_executable(lua_State* L);
void smake_register_api(lua_State* L);