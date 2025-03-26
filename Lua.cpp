#include "Lua.h"
std::vector<LuaModel> Lua::models;

void Lua::InitLua() {
    L = luaL_newstate();
    luaL_openlibs(L);
    RegisterFunctions();

    // Load the Lua script
    if (luaL_dofile(L, "LuaScripts/LuaScript.lua") != LUA_OK) {
        std::cerr << "Error running Lua script: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);  // Pop the error message
    }

    // Call the Start function if it exists
    lua_getglobal(L, "Start");
    if (lua_isfunction(L, -1)) {
        if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            std::cerr << "Error calling Start function: " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);  // Pop the error message
        }
    }
    else {
        std::cerr << "Start function not found in Lua script." << std::endl;
    }
}

void Lua::RunLuaScript(float deltaTime) {
    lua_getglobal(L, "Update");
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, deltaTime);
        if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
            std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);
        }
    }
    else {
        lua_pop(L, 1);
        std::cerr << "Lua function 'Update' not found!" << std::endl;
    }
}

void Lua::RegisterFunctions() {
    lua_register(L, "createObject", Lua::createObject);
    lua_register(L, "setPosition", Lua::setPosition);
    lua_register(L, "setRotation", Lua::setRotation);
    lua_register(L, "setScale", Lua::setScale);
}

int Lua::createObject(lua_State* L) {
    const char* model = luaL_checkstring(L, 1);
    const char* texture = luaL_checkstring(L, 2);

    models.emplace_back(model, texture);
    lua_pushinteger(L, models.size());  // Return the index (0-based)
    return 1;
}

int Lua::setPosition(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1; // Adjust to 0-based index
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    float z = luaL_checknumber(L, 4);

    if (id >= 0 && id < models.size()) {
        models[id].setPosition(x, y, z);
    }
    else {
        std::cerr << "setPosition: Invalid model ID " << id << std::endl;
    }

    return 0;
}

int Lua::setRotation(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1; // Adjust to 0-based index
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    float z = luaL_checknumber(L, 4);
    float w = luaL_checknumber(L, 5);

    if (id >= 0 && id < models.size()) {
        models[id].setRotation(x, y, z, w);
    }
    else {
        std::cerr << "setRotation: Invalid model ID " << id << std::endl;
    }

    return 0;
}

int Lua::setScale(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1; // Adjust to 0-based index
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    float z = luaL_checknumber(L, 4);

    if (id >= 0 && id < models.size()) {
        models[id].setScale(x, y, z);
    }
    else {
        std::cerr << "setScale: Invalid model ID " << id << std::endl;
    }

    return 0;
}
