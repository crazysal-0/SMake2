#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>

char* read_file_to_string(const char* path) {
  FILE* file = fopen(path, "rb");

  if (!file) return NULL;

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char* buffer = malloc(size + 1);

  if (!buffer) {
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, size, file);
  buffer[size] = '\0';

  fclose(file);

  return buffer;
}

int main(int argc, char** argv) {
  char* smake_lua = read_file_to_string("smake.lua");

  if (smake_lua == NULL) {
    fputs("error: smake.lua not found\n", stderr);
    return 1;
  }

  lua_State* lua_state = luaL_newstate();
  luaL_openlibs(lua_state);

  if (luaL_dostring(lua_state, smake_lua) != 0) {
    fprintf(stderr, "smake: lua error\n", lua_tostring(lua_state, -1));
  }

  lua_close(lua_state);

  return 0;
}