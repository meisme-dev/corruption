#include "Sprite.hpp"

Sprite::Sprite(){
	
}

Sprite::Sprite(bgfx::TextureHandle texture_handle, bgfx::ProgramHandle shader_program, bgfx::UniformHandle uniform_handle, uint64_t state, uint32_t flags) :
	texture_handle(texture_handle),
	shader_program(shader_program),
	uniform_handle(uniform_handle),
	state(state),
	flags(flags) {
	create();
}


Sprite::~Sprite() {

}

void Sprite::create() {
	bgfx::VertexLayout pvcDecl;
	pvcDecl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.end();
	vbh = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), pvcDecl);
	ibh = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));
}

void Sprite::render() {
	bgfx::setTexture(0, uniform_handle, texture_handle, BGFX_SAMPLER_POINT | BGFX_SAMPLER_UVW_CLAMP);
	bgfx::setVertexBuffer(0, vbh);
	bgfx::setIndexBuffer(ibh);
	bgfx::setState(state);
	bgfx::submit(0, shader_program);
}
