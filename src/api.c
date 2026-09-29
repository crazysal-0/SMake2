#include "api.h"

#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smake_run_cmd(lua_State* L) {
  luaL_checktype(L, 1, LUA_TTABLE);

  size_t command_length = 0;

  lua_pushnil(L);

  while (lua_next(L, 1) != 0) {
    luaL_checktype(L, -1, LUA_TSTRING);

    command_length += strlen(lua_tostring(L, -1)) + 1;

    lua_pop(L, 1);
  }

  char* command = malloc(command_length + 1);

  if (command == NULL) {
    return luaL_error(L, "failed to allocate command");
  }

  command[0] = '\0';

  lua_pushnil(L);

  while (lua_next(L, 1) != 0) {
    const char* arg = lua_tostring(L, -1);

    strcat(command, arg);
    strcat(command, " ");

    lua_pop(L, 1);
  }

  printf("> %s\n", command);

  int result = system(command);

  free(command);

  if (result != 0) {
    return luaL_error(L, "command failed");
  }

  return 0;
}

int smake_target_executable(lua_State* L) {
  const char* name = luaL_checkstring(L, 1);

  luaL_checktype(L, 2, LUA_TTABLE);
  luaL_checktype(L, 3, LUA_TTABLE);

  const char* compiler = luaL_checkstring(L, 4);

  lua_newtable(L);

  int command = lua_gettop(L);
  int index = 1;

  // compiler
  lua_pushstring(L, compiler);
  lua_rawseti(L, command, index++);

  // -o
  lua_pushstring(L, "-o");
  lua_rawseti(L, command, index++);

  // output name
  lua_pushstring(L, name);
  lua_rawseti(L, command, index++);

  // sources
  lua_pushnil(L);

  while (lua_next(L, 2) != 0) {
    lua_pushvalue(L, -1);
    lua_rawseti(L, command, index++);

    lua_pop(L, 1);
  }

  // flags
  lua_pushnil(L);

  while (lua_next(L, 3) != 0) {
    lua_pushvalue(L, -1);
    lua_rawseti(L, command, index++);

    lua_pop(L, 1);
  }

  // Call smake_run_cmd(command)
  lua_pushcfunction(L, smake_run_cmd);
  lua_pushvalue(L, command);
  lua_call(L, 1, 0);

  return 0;
}

void smake_register_api(lua_State* L) {
  lua_register(L, "run_cmd", smake_run_cmd);
  lua_register(L, "target_executable", smake_target_executable);
}