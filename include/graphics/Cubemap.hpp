#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include "graphics/Shader.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include "math/Mat4.hpp"
#include <vector>

namespace renderel::graphics {

class Cubemap {
  private:
	unsigned int m_TextureID;
	Shader *m_Shader;

	VertexArray *m_Va;
	VertexBuffer *m_Vb;

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
			const std::vector<std::string> &shaders);
	~Cubemap();

	unsigned int getTextureID() { return m_TextureID; }
	void UseShader() const;
	void UnuseShader() const;
	void BindTexture() const;
	void UnbindTexture() const;
	void Draw() const;
	void SetViewMatrix(const math::Mat4<float> &mat);
	void SetProjectionMatrix(const math::Mat4<float> &mat);
};

} // namespace renderel::graphics

#endif // !CUBEMAP_HPP
