#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include "core/Common.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/Texture.hpp"
#include "math/Mat4.hpp"
#include <vector>

namespace renderel::graphics {

class Cubemap {
  private:
	Shader m_Shader;
	Texture m_Texture;
	uint32 m_TextureID;

	std::unique_ptr<VertexArray> m_Va;
	std::unique_ptr<VertexBuffer> m_Vb;
	std::unique_ptr<IndexBuffer> m_Ib;

	math::Mat4<float> m_ViewMatrix;
	math::Mat4<float> m_ProjectionMatrix;
	Renderer renderer;

	static constexpr float size = 1.0f;

	static constexpr float m_SkyboxVertices[] = {
		// positions
		-size, size,  -size, //
		-size, -size, -size, //
		size,  -size, -size, //
		size,  -size, -size, //
		size,  size,  -size, //
		-size, size,  -size, //

		-size, -size, size,  //
		-size, -size, -size, //
		-size, size,  -size, //
		-size, size,  -size, //
		-size, size,  size,  //
		-size, -size, size,  //

		size,  -size, -size, //
		size,  -size, size,  //
		size,  size,  size,  //
		size,  size,  size,  //
		size,  size,  -size, //
		size,  -size, -size, //

		-size, -size, size, //
		-size, size,  size, //
		size,  size,  size, //
		size,  size,  size, //
		size,  -size, size, //
		-size, -size, size, //

		-size, size,  -size, //
		size,  size,  -size, //
		size,  size,  size,  //
		size,  size,  size,  //
		-size, size,  size,  //
		-size, size,  -size, //

		-size, -size, -size, //
		-size, -size, size,  //
		size,  -size, -size, //
		size,  -size, -size, //
		-size, -size, size,  //
		size,  -size, size   //
	};

	static constexpr unsigned int indices[] = {
		0,  1,  2,  //
		3,  4,  5,  //
		6,  7,  8,  //
		9,  10, 11, //
		12, 13, 14, //
		15, 16, 17, //
		18, 19, 20, //
		21, 22, 23, //
		24, 25, 26, //
		27, 28, 29, //
		30, 31, 32, //
		33, 34, 35  //
	};

  public:
	// faces are {right, left, top, bottom, front, back}
	Cubemap(const std::vector<std::string> &faces,
			const std::string &vertexShaderPath,
			const std::string &fragmentShaderPath);
	~Cubemap();

	void Draw();
	void SetViewMatrix(const math::Mat4<float> &mat);
	void SetProjectionMatrix(const math::Mat4<float> &mat);
};

} // namespace renderel::graphics

#endif // !CUBEMAP_HPP
