#include "api.h"

#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smake_target_executable(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);

  luaL_checktype(L, 2, LUA_TTABLE);
  luaL_checktype(L, 3, LUA_TTABLE);
  luaL_checkstring(L, 4);

  const char* compiler = lua_tostring(L, 4);

  printf("building executable: %s\n", name);
  printf("compiler: %s\n", compiler);

  return 0;
}

void smake_register_api(lua_State* L) {
  lua_register(L, "target_executable", smake_target_executable);
}