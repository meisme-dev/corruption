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
#include <thread>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "Engine/Texture.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/AnimatedSprite.hpp"

class Game {
public:
    Game(int height, int width, GLFWwindow* window);
    ~Game();
    void loop();

private:
    int height;
    int width;
    GLFWwindow* window;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Shader> shader;
    bgfx::ProgramHandle shader_program;
    bgfx::TextureHandle texture_handle[2];
    bgfx::UniformHandle s_texColor;
};

#endif
