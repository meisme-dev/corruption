#include "Shader.hpp"

Shader::Shader() {

}

template void Asset<bgfx::ShaderHandle>::create();
bgfx::ShaderHandle Shader::create(std::string path, bgfx::RendererType::Enum renderer_type) {
	std::string platform_path = "/Assets/Shaders/glsl";
	switch (renderer_type)
	{
	case bgfx::RendererType::Vulkan :
		platform_path = "/Assets/Shaders/spirv/";
		break;
	case bgfx::RendererType::OpenGL :
		platform_path = "/Assets/Shaders/440/";
		break;
	case bgfx::RendererType::Direct3D9 :
	case bgfx::RendererType::Direct3D11 :
	case bgfx::RendererType::Direct3D12 :
		platform_path = "/Assets/Shaders/s_5_0/";
		break;
	case bgfx::RendererType::Metal :
		platform_path = "/Assets/Shaders/metal/";
		break;
	case bgfx::RendererType::OpenGLES :
		platform_path = "/Assets/Shaders/320_es/";
		break;
	default:
		break;
	}
	std::string asset_path = get_asset_path(platform_path + path);
	size_t f_size = std::filesystem::file_size(asset_path);
	std::string shader_contents = get_file_contents(asset_path);
	buf = bgfx::copy(shader_contents.data(), f_size + 1);
	buf->data[buf->size - 1] = '\0';
	return bgfx::createShader(buf);
}