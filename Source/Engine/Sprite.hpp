#ifndef SPRITE_H
#define SPRITE_H

#pragma once

#define BX_CONFIG_DEBUG true

#include <bgfx/bgfx.h>
#include <bx/math.h>

class Sprite{
public:
    Sprite(bgfx::TextureHandle texture_handle, bgfx::ProgramHandle shader_program, uint64_t state, uint32_t flags);
    ~Sprite();
    void render();

private:
    void create();
    bgfx::TextureHandle texture_handle;
    bgfx::ProgramHandle shader_program;
    bgfx::VertexBufferHandle vbh;
    bgfx::IndexBufferHandle ibh;
    bgfx::UniformHandle texture_uniform;
    uint64_t state;
    uint32_t flags;

    struct ColorVertex {
        float x;
        float y;
        float z;
        float u;
        float v;
    } vertices[4] = {
        {-1.0f, -1.0f,  0.0f,  0.0f,  0.0f}, // Bottom left
        {-1.0f,  1.0f,  0.0f,  0.0f,  1.0f}, // Top left
        { 1.0f,  1.0f,  0.0f,  1.0f,  1.0f}, // Top right
        { 1.0f, -1.0f,  0.0f,  1.0f,  0.0f}, // Bottom right
    };

    static constexpr uint16_t indices[] = {
        0, 1, 2,
        0, 2, 3,
    };
};

#endif