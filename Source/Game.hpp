#ifndef GAME_H
#define GAME_H

#pragma once
#define BX_CONFIG_DEBUG true

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>
#include <iostream>
#include <memory>
#include <bx/math.h>
#include <chrono>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "Engine/Texture.hpp"
#include "Engine/Shader.hpp"

struct PosColorVertex {
    float x;
    float y;
    float z;
    float u;
    float v;
    uint32_t abgr;
};

static PosColorVertex vertices[] = {
    {-1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0x00000000 }, // Bottom left
    {-1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0x00000000 }, // Top left
    { 1.0f,  1.0f,  0.0f,  1.0f,  1.0f, 0x00000000 }, // Top right
    { 1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0x00000000 }, // Bottom right
};

static const uint16_t indices[] = {
    0, 1, 2,
    0, 2, 3,
};

class Game {
public:
    Game(int height, int width, GLFWwindow *window);
    ~Game();
    void loop();

private:
    int height;
    int width;
    GLFWwindow* window;
    bgfx::ShaderHandle water_fsh;
    bgfx::ShaderHandle water_vsh;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Shader> shader;
    bgfx::ProgramHandle shader_program;
    bgfx::TextureHandle texture_handle[10];
    bgfx::UniformHandle s_texColor;
};

#endif