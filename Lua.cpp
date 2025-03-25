#include "Lua.h"

int Lua::LuaTest() {
    lua_State* L = luaL_newstate();
    if (!L) {
        std::cerr << "Failed to create Lua state\n";
        return 1;
    }

    luaL_openlibs(L);

    if (luaL_dofile(L, "LuaScripts/test.lua") != LUA_OK) {
        std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    else {
        std::cout << "Lua script executed successfully!" << std::endl;
    }

    lua_close(L);
    return 0;
}

void Lua::RunLuaScript() {
    lua_State* A = luaL_newstate();
    if (!A) {
        std::cerr << "Failed to create Lua state\n";
        return;
    }

    luaL_openlibs(A);

    luaL_dofile(A, "LuaScripts/LuaScript.lua");

    lua_close(A);
    return;
}