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
#define GLFW_EXPOSE_NATIVE_WAYLAND
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>
#include <cstdio>

class Initialize {
public:
    Initialize(int height, int width, const char* title);
    ~Initialize();

private:
    void init();
    bgfx::Init bgfxInit;
    GLFWwindow* window;
    char* path;
    int height;
    int width;
    const char* title;
};

#endif