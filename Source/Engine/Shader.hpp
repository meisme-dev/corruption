#ifndef SHADER_H
#define SHADER_H

#pragma once

#include "Asset.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

class Shader : public Asset<bgfx::ShaderHandle> {
public:
    Shader();
    bgfx::ShaderHandle create(std::string path, bgfx::RendererType::Enum renderer_type);

private:
    const bgfx::Memory* buf;
};

#endif