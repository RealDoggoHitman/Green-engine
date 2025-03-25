#ifndef LUA_H
#define LUA_H

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <iostream>
#include <string>

class Lua {
public:
    int LuaTest();
    void RunLuaScript();
};

#endif
