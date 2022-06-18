#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() {

}

template void Asset<bgfx::TextureHandle>::create();
bgfx::TextureHandle Texture::create(std::string path,
	int height, int width, bool has_mips, int layers, bgfx::TextureFormat::Enum texture_format, uint64_t flags) {
	std::string file_path = get_asset_path(path);
	size_t f_size = std::filesystem::file_size(file_path);
	std::string texture_contents = get_file_contents(file_path);
	int w, h, c;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file_path.c_str(), &w, &h, &c, 4);
	buf = bgfx::copy(data, w * h * 4);
	return bgfx::createTexture2D(w, h, has_mips, layers, texture_format, BGFX_SAMPLER_POINT, buf);
}