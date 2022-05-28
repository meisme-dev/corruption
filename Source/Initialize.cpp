#include "Initialize.hpp"

Initialize::Initialize(int height, int width, const char* title, char *path) {
	this->height = height;
	this->width = width;
	this->title = title;

	if(!glfwInit()){
		std::cout << "Failed to initialize GLFW" << std::endl;
	}
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		bgfxInit.platformData.ndt = glfwGetX11Display();
		bgfxInit.platformData.nwh = (void*)(uintptr_t) glfwGetX11Window(window);
	#elif BX_PLATFORM_OSX
		init.platformData.nwh = glfwGetCocoaWindow(window);
	#elif BX_PLATFORM_WINDOWS
		init.platformData.nwh = glfwGetWin32Window(window);
	#endif

	bgfxInit.resolution.width = width;
	bgfxInit.resolution.height = height;
	bgfxInit.resolution.reset  = BGFX_RESET_VSYNC;
	bgfxInit.debug = BGFX_DEBUG_TEXT;
	bgfxInit.type = bgfx::RendererType::Vulkan;
}

Initialize::~Initialize() {

}

void Initialize::init() {
	bgfx::renderFrame();
	if(!bgfx::init(bgfxInit)){
		std::cout << "Failed to initialize bgfx" << std::endl;
	}

	switch(bgfx::getRendererType()){
		case bgfx::RendererType::Direct3D11:
			std::cout << "Using Direct3D11 as renderer backend" << std::endl;
			break;
		case bgfx::RendererType::Direct3D9:
			std::cout << "Using Direct3D9 renderer" << std::endl;
			break;
		case bgfx::RendererType::OpenGL:
			std::cout << "Using OpenGL renderer" << std::endl;
			break;
		case bgfx::RendererType::OpenGLES:
			std::cout << "Using OpenGLES as renderer backend" << std::endl;
			break;
		case bgfx::RendererType::Vulkan:
			std::cout << "Using Vulkan renderer" << std::endl;
			break;
		case bgfx::RendererType::Metal:
			std::cout << "Using Metal as renderer backend" << std::endl;
			break;
		default:
			std::cout << "Using an unknown renderer backend" << std::endl;
			break;
	}

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
	game = std::make_shared<Game>(height, width, window);
	game->loop();
}