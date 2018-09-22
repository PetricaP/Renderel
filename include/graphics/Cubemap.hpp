#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include "core/Common.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include "math/Mat4.hpp"
#include <vector>

namespace renderel::graphics {

class Cubemap {
  private:
	Shader *m_Shader;
	Texture texture;
	uint32 m_TextureID;

	std::unique_ptr<VertexArray> m_Va;
	std::unique_ptr<VertexBuffer> m_Vb;

	math::Mat4<float> m_ViewMatrix;
	math::Mat4<float> m_ProjectionMatrix;

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

  public:
	// faces are {right, left, top, bottom, front, back}
	Cubemap(const std::vector<std::string> &faces,
			const std::string &vertexShaderPath,
			const std::string &fragmentShaderPath);
	~Cubemap();

	void Draw() const;
	void SetViewMatrix(const math::Mat4<float> &mat);
	void SetProjectionMatrix(const math::Mat4<float> &mat);
};

} // namespace renderel::graphics

#endif // !CUBEMAP_HPP
