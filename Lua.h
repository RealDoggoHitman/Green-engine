#ifndef LUA_H
#define LUA_H

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

struct Transform {
    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
};


class LuaModel {
public:
    std::string modelPath;
    std::string texturePath;
    Transform transform;

    LuaModel(const std::string& modelPath, const std::string& texturePath)
        : modelPath(modelPath), texturePath(texturePath) {}

    void setPosition(float x, float y, float z) {
        transform.position = glm::vec3(x, y, z);
    }

    void setRotation(float x, float y, float z, float w) {
        transform.rotation = glm::quat(w, x, y, z);
    }

    void setScale(float x, float y, float z) {
        transform.scale = glm::vec3(x, y, z);
    }
};

class Lua {
public:
    lua_State* L;
    void InitLua();
    void RunLuaScript(float deltaTime);
    void RegisterFunctions();

    static std::vector<LuaModel> models; 
    static int createObject(lua_State* L);
    static int setPosition(lua_State* L);
    static int setRotation(lua_State* L);
    static int setScale(lua_State* L);
};

#endif
