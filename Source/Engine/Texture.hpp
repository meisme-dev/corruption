#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define BX_CONFIG_DEBUG true

#pragma once

#include "Asset.hpp"

#include <bimg/bimg.h>
#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

class Texture : public Asset<bgfx::TextureHandle>{
public:
    Texture();
    bgfx::TextureHandle create(std::string path, 
    int height, int width, bool has_mips, int layers, bgfx::TextureFormat::Enum texture_format, uint64_t flags);

private:
    const bgfx::Memory *buf;
};

#endif