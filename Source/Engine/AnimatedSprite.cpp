#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(bgfx::TextureHandle texture_handle[], bgfx::ProgramHandle shader_program, 
bgfx::UniformHandle uniform_handle, uint64_t state, uint32_t flags, uint32_t frame_count, uint16_t delay) {
	for (int i = 0; i < frame_count; i++) {
		this->texture_handle.push_back(texture_handle[i]);
	}
	this->shader_program = shader_program;
	this->uniform_handle = uniform_handle;
	this->state = state;
	this->flags = flags;
	this->frame_count = frame_count;
	this->delay = delay;
	this->current_frame = 0;
	create();
}

AnimatedSprite::~AnimatedSprite() {
	
}

void AnimatedSprite::render(double delta) {
	last += delta;
	if (delay - last < 0) {
		current_frame++;
		last = 0;
	}
	if (current_frame >= frame_count) {
		current_frame = 0;
	}
	bgfx::setTexture(0, uniform_handle, texture_handle.at(current_frame), BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP);
	bgfx::setVertexBuffer(0, vbh);
	bgfx::setIndexBuffer(ibh);
	bgfx::setState(state);
	bgfx::submit(0, shader_program);
}