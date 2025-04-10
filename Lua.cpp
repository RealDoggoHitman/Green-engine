#include "Lua.h"
#include <filesystem>
std::vector<LuaModel> Lua::models;

namespace fs = std::filesystem;

static std::string currentScriptPath;



void Lua::InitLua() {
    models.clear();
    if (L) {
        lua_close(L);
        L = nullptr;
    }

    L = luaL_newstate();
    luaL_openlibs(L);
    RegisterFunctions();

    if (luaL_dofile(L, "LuaScripts/Main.lua") != LUA_OK) {
        std::cerr << "Error running Lua script: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    lua_getglobal(L, "Start");
    if (lua_isfunction(L, -1)) {
        if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            std::cerr << "Error calling Start function: " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);
        }
    }
    else {
        std::cerr << "Start function not found in Lua script." << std::endl;
        lua_pop(L, 1);
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

    // Position
    lua_register(L, "setPosition", Lua::setPosition);
    lua_register(L, "setX", Lua::setX);
    lua_register(L, "setY", Lua::setY);
    lua_register(L, "setZ", Lua::setZ);

    // Rotation
    lua_register(L, "setRotation", Lua::setRotation);
    lua_register(L, "setRotX", Lua::setRotX);
    lua_register(L, "setRotY", Lua::setRotY);
    lua_register(L, "setRotZ", Lua::setRotZ);

    // Scale
    lua_register(L, "setScale", Lua::setScale);
    lua_register(L, "setScaleX", Lua::setScaleX);
    lua_register(L, "setScaleY", Lua::setScaleY);
    lua_register(L, "setScaleZ", Lua::setScaleZ);
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

int Lua::setX(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1; // Adjust to 0-based index
    float x = luaL_checknumber(L, 2);

    if (id >= 0 && id < models.size()) {
        models[id].setX(x);
    }
    else {
        std::cerr << "setX: Invalid model ID " << id << std::endl;
    }
    return 0;
}

int Lua::setY(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1;
    float y = luaL_checknumber(L, 2);

    if (id >= 0 && id < models.size()) {
        models[id].setY(y);
    }
    else {
        std::cerr << "setY: Invalid model ID " << id << std::endl;
    }
    return 0;
}

int Lua::setZ(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1;
    float z = luaL_checknumber(L, 2);

    if (id >= 0 && id < models.size()) {
        models[id].setZ(z);
    }
    else {
        std::cerr << "setZ: Invalid model ID " << id << std::endl;
    }
    return 0;
}

int Lua::setRotation(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1; // Adjust to 0-based index
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    float z = luaL_checknumber(L, 4);

    if (id >= 0 && id < models.size()) {
        models[id].setRotation(x, y, z);
    }
    else {
        std::cerr << "setRotation: Invalid model ID " << id << std::endl;
    }

    return 0;
}

int Lua::setRotX(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1;
    float x = luaL_checknumber(L, 2);
    if (id >= 0 && id < models.size()) models[id].setRotX(x);
    return 0;
}

int Lua::setRotY(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1;
    float y = luaL_checknumber(L, 2);
    if (id >= 0 && id < models.size()) models[id].setRotY(y);
    return 0;
}

int Lua::setRotZ(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1;
    float z = luaL_checknumber(L, 2);
    if (id >= 0 && id < models.size()) models[id].setRotZ(z);
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

int Lua::setScaleX(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1;
    float x = luaL_checknumber(L, 2);
    if (id >= 0 && id < models.size()) models[id].setScaleX(x);
    return 0;
}

int Lua::setScaleY(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1;
    float y = luaL_checknumber(L, 2);
    if (id >= 0 && id < models.size()) models[id].setScaleY(y);
    return 0;
}

int Lua::setScaleZ(lua_State* L) {
    int id = luaL_checkinteger(L, 1) - 1;
    float z = luaL_checknumber(L, 2);
    if (id >= 0 && id < models.size()) models[id].setScaleZ(z);
    return 0;
}
