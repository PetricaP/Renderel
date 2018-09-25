#include "test/TestTriangleColor.hpp"

namespace renderel::test {

TestTriangleColor::TestTriangleColor(const Window &window)
	: Test(window), m_Colors{math::Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f),
							 math::Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f),
							 math::Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f)},
	  shader("shaders/vertexShaderColor.glsl",
			 "shaders/fragmentShaderColor.glsl") {

	va = std::make_unique<graphics::VertexArray>();

	vb = std::make_unique<graphics::VertexBuffer>(m_Vertices, 4,
												  sizeof(float) * 3 + sizeof(int32));

	graphics::VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<int32>(1);

	va->AddBuffer(std::move(vb), vbl);

	ib = std::make_unique<graphics::IndexBuffer>(
		m_Indices, sizeof(m_Indices) / sizeof(m_Indices[0]));

	shader.Bind();
}

TestTriangleColor::~TestTriangleColor() {}

void TestTriangleColor::OnUpdate(float) {
	math::Mat4<float> colorMatrix(m_Colors[0], m_Colors[1], m_Colors[2],
								  math::Vec4<float>(1.0f));
	shader.SetUniformMat4f("u_ColorMatrix", colorMatrix);
}

void TestTriangleColor::OnRender() {
	m_Window.GetRenderer()->Clear();
	m_Window.GetRenderer()->Submit(graphics::Renderable(shader, va.get(), ib.get()));
	m_Window.GetRenderer()->Flush();
}

void TestTriangleColor::OnGUIRender() {
	GUI *gui = m_Window.GetGUI();
	gui->ColorEdit4("First corner", m_Colors[0].elements);
	gui->ColorEdit4("Second corner", m_Colors[1].elements);
	gui->ColorEdit4("Third corner", m_Colors[2].elements);
}

} // namespace renderel::test
