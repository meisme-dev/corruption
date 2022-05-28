#ifndef INITIALIZE_H
#define INITIALIZE_H

#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <memory>

#include "Game.hpp"

#if BX_PLATFORM_LINUX
    #define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
    #define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>
#include <cstdio>

class Initialize {
public:
    Initialize(int height, int width, const char* title, char *path);
    ~Initialize();
    void init();

private:
    bgfx::Init bgfxInit;
    GLFWwindow *window;
    std::shared_ptr<Game> game;
    char *path;
    int height;
    int width;
    const char* title;
};

#endif