#include "Shader.hpp"

Shader::Shader(){

}

template void Asset<bgfx::ShaderHandle>::create();
bgfx::ShaderHandle Shader::create(std::string path){
	std::string asset_path = get_asset_path(path);
    size_t f_size = std::filesystem::file_size(asset_path);
	std::string shader_contents = get_file_contents(asset_path);
	buf = bgfx::copy(shader_contents.data(), f_size+1);
	buf->data[buf->size-1] = '\0';
	return bgfx::createShader(buf);
}