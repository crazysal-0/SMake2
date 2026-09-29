CC = "gcc"

CFLAGS = {
    "-Wall",
    "-Wextra",
    "-std=c11",
    "-Iinc",
    "-I/usr/include/lua5.4"
}

LDFLAGS = { "-llua5.4" }

SOURCES = {
    "src/main.c",
    "src/api.c"
}

target_executable("bin/smake", SOURCES, CFLAGS, LDFLAGS, CC)