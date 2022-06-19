#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#pragma once

#include <cstdint>
#include <vector>
#include "Sprite.hpp"

class AnimatedSprite : public Sprite {
public:
    explicit AnimatedSprite(bgfx::TextureHandle texture_handle[], bgfx::ProgramHandle shader_program, 
    bgfx::UniformHandle uniform_handle, uint64_t state, uint32_t flags, uint32_t frame_count, uint16_t delay);
    ~AnimatedSprite();
    void render(double delta);
private:
    std::vector<bgfx::TextureHandle> texture_handle;
    uint32_t current_frame;
    double last;
    uint16_t frame_count, delay;
};

#endif