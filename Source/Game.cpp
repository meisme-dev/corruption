#include "Game.hpp"

Game::Game(int height, int width, GLFWwindow* window) :
	height(height),
	width(width),
	window(window) {
	texture = std::make_shared<Texture>();
	shader = std::make_shared<Shader>();
	bgfx::RendererType::Enum renderer_type = bgfx::getRendererType();
	bgfx::ShaderHandle fsh_handle = shader->create("sprite.fsh.bin", renderer_type);
	bgfx::ShaderHandle vsh_handle = shader->create("default.vsh.bin", renderer_type);
	shader_program = bgfx::createProgram(vsh_handle, fsh_handle, false);
	uint64_t flags = BGFX_TEXTURE_NONE;
	texture_handle[0] = texture->create("/Assets/Textures/ball_alt.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	texture_handle[1] = texture->create("/Assets/Textures/bg.png", 0, 0, false, 1, bgfx::TextureFormat::RGBA8, flags);
	bgfx::destroy(fsh_handle);
	bgfx::destroy(vsh_handle);
	s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
}

Game::~Game() {
	std::cout << "\e[?25h";
}

void Game::loop() {
	uint8_t counter = 0;
	double delta = 0.0, last = 0.0, jump_t = 0.0;
	float mvx = 0, mvy = 0;
	bool jump = false;
	std::unique_ptr<Sprite> sprite(
		new Sprite(shader_program,
			s_texColor,
			BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA) | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A,
			BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP));

	std::unique_ptr<Sprite> sprite_2(
		new Sprite(shader_program,
			s_texColor,
			BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA) | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A,
			BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP));

	while (!glfwWindowShouldClose(window)) {
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		glfwGetWindowSize(window, &width, &height);
		bgfx::reset(width, height, BGFX_RESET_NONE);
		const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
		float view[16];
		bx::mtxLookAt(view, eye, at);
		float proj[16];
		bx::mtxProj(proj, 60.0f, float(width) / float(height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(0, view, proj);
		bgfx::setViewRect(0, 0, 0, width, height);

		if ((glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS && mvy < 0.5) {
			mvx += delta / 100.0f;
		}
		if ((glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS && mvy < 0.5) {
			mvx -= delta / 100.0f;
		}
		if ((glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS && mvy < 3.0f) {
			jump = true;
			mvy += delta / 100.0f;
		}
		if ((glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS && mvy > 0.0f) {
			mvy -= delta / 100.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			break;
		}

		bgfx::touch(0);
		last += delta;
		jump_t += delta;
		if (5 - last < 0) {
			if(mvy > 0 && jump == false)
				mvy -= delta / 25.0f;
			counter++;
			last = 0;
		}
		if(250 - jump_t < 0) {
			jump = false;
			jump_t = 0;
		}
		if (counter > 9) {
			counter = 0;
		}
		framebuffer[0] = bgfx::createFrameBuffer(width, height, bgfx::TextureFormat::BGRA8, BGFX_SAMPLER_UVW_CLAMP);
		bgfx::setViewFrameBuffer(0, framebuffer[0]);
		bgfx::TextureHandle test = bgfx::getTexture(framebuffer[0]);
		float mtx[16];
		bx::mtxSRT(mtx, 5.32f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, -(mvx * 0.75f), 0.0f, -1.0f);
		bgfx::setTransform(mtx);
		sprite_2->render(texture_handle[1]);
		bx::mtxSRT(mtx, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, mvx * 0.5f, 0.0f, -1.5f + mvy, 0.0f);
		bgfx::setTransform(mtx);
		sprite->render(texture_handle[0]);
		//pass current framebuffer to shader
		//Call bgfx::frame twice to avoid flickering
		bgfx::frame();
		bgfx::frame();
		delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
		delta /= 1000.0f;
		if (delta == 0) {
			delta = 0.1;
		}
		glfwPollEvents();
	}

	bgfx::shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();
	return;
}
