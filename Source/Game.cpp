#include "Game.hpp"

Game::Game(int height, int width, GLFWwindow *window) :
height(height),
width(width),
window(window){
	texture = std::make_shared<Texture>();
	shader = std::make_shared<Shader>();
	bgfx::ShaderHandle fsh_handle = shader->create("/Assets/Shaders/water.fsh.bin");
	bgfx::ShaderHandle vsh_handle = shader->create("/Assets/Shaders/water.vsh.bin");
	shader_program = bgfx::createProgram(vsh_handle, fsh_handle, false);
	
	uint64_t flags = BGFX_TEXTURE_NONE;
	texture_handle[0] = texture->create("/Assets/Textures/test4.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[1] = texture->create("/Assets/Textures/test5.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[2] = texture->create("/Assets/Textures/test6.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[3] = texture->create("/Assets/Textures/test7.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[4] = texture->create("/Assets/Textures/test8.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[5] = texture->create("/Assets/Textures/test9.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[6] = texture->create("/Assets/Textures/test10.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[7] = texture->create("/Assets/Textures/test11.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[8] = texture->create("/Assets/Textures/test12.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[9] = texture->create("/Assets/Textures/test13.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle_test = texture->create("/Assets/Textures/ball.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	bgfx::destroy(fsh_handle);
	bgfx::destroy(vsh_handle);
	s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
}

Game::~Game() {
	std::cout << "\e[?25h";
}

void Game::loop() {
	unsigned int counter = 0;
	// bgfx::VertexLayout pcvDecl;
	// pcvDecl.begin()
	// 	.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
	// 	.add( bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float )
	// 	.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
	// .end();
	double delta = 0.0, last = 0.0;
	float mvx = 0, mvy = 0;
	// bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), pcvDecl);
	// bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));
	
	std::unique_ptr<Sprite> sprite(
	new Sprite(texture_handle[0], 
	shader_program, 
	BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA) | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A, 
	BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP));

	std::unique_ptr<Sprite> sprite_2(
	new Sprite(texture_handle[1], 
	shader_program, 
	BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA) | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A, 
	BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP));

	while(!glfwWindowShouldClose(window)){
		std::chrono::system_clock::time_point start = std::chrono::high_resolution_clock::now();
		glfwGetWindowSize(window, &width, &height);
		bgfx::reset(width, height, BGFX_RESET_NONE);
        const bx::Vec3 at = {0.0f, 0.0f,  0.0f};
        const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};
        float view[16];
        bx::mtxLookAt(view, eye, at);
        float proj[16];
        bx::mtxProj(proj, 60.0f, float(width) / float(height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);
		bgfx::setViewRect(0, 0, 0, width, height);
   	    // float mtx[16];	
		// // bx::mtxRotateXY(mtx, bx::sin(counter * 0.02) * 3, bx::sin(counter * 0.02) * 3);
		// bgfx::setTransform(mtx);
		// bx::mtxTranslate(mtx, mvx, mvy, 0.0f);
		if((glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS){
			mvx += delta / 100.0f;
		}
		if((glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS){
			mvx -= delta / 100.0f;
		}
		if((glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS){
			mvy += delta / 100.0f;
		}
		if((glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS){
			mvy -= delta / 100.0f;
		}
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			break;
		}
		bgfx::touch(0);
		last += delta;
		if(100 - last < 0) {
			counter++;
			last = 0;
		}
		if(counter > 9){
			counter = 0;
		}
		bgfx::setTexture(0, s_texColor, texture_handle_test, BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP);
		float mtx[16];
		bx::mtxRotateZ(mtx, mvx * 0.5f);
		bx::mtxTranslate(mtx, mvx, mvy, 0.0f);
		bx::mtxScale(mtx, 0.5f, 0.5f, 0.5f);
		bgfx::setTransform(mtx);
		sprite->render();
		bgfx::frame();
		delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
		delta /= 1000.0f;
		if(delta == 0){
			delta = 0.1;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	bgfx::shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();
	return;
}