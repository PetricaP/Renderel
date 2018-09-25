#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace renderel::graphics {

struct Renderable {
	const VertexArray *va;
	const IndexBuffer *ib;
	Shader &shader;

	Renderable(Shader &shader, const VertexArray *va,
			   const IndexBuffer *ib = nullptr)
		: va(va), ib(ib), shader(shader) {}

	~Renderable() = default;
};

} // namespace renderel::graphics

#endif // RENDERABLE_HPP
