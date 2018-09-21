#include "test/TestTriangleColor.hpp"

namespace renderel::test {

TestTriangleColor::TestTriangleColor(const Window &window)
	: Test(window), m_Colors{math::Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f),
							 math::Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f),
							 math::Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f)} {

	va = new graphics::VertexArray();

	vb = new graphics::VertexBuffer(m_Vertices, sizeof(m_Vertices));

	graphics::VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<int32>(1);

	va->AddBuffer(vb, vbl);

	ib = new graphics::IndexBuffer<uint32>(m_Indices, sizeof(m_Indices) /
														  sizeof(m_Indices[0]));

	renderer = new graphics::BasicRenderer();

	shader = new graphics::Shader("shaders/vertexShaderColor.glsl",
								  "shaders/fragmentShaderColor.glsl");

	shader->Bind();
}

TestTriangleColor::~TestTriangleColor() {
	delete shader;
	delete va;
	delete ib;
	delete renderer;
}

void TestTriangleColor::OnUpdate(float) {
	math::Mat4<float> colorMatrix(m_Colors[0], m_Colors[1], m_Colors[2],
								  math::Vec4<float>(1.0f));
	shader->SetUniformMat4f("u_ColorMatrix", colorMatrix);
}

void TestTriangleColor::OnRender() {
	renderer->Clear();
	renderer->Submit(graphics::Renderable(va, ib, *shader));
	renderer->Flush();
}

void TestTriangleColor::OnGUIRender() {
	GUI *gui = m_Window.GetGUI();
	gui->ColorEdit4("First corner", m_Colors[0].elements);
	gui->ColorEdit4("Second corner", m_Colors[1].elements);
	gui->ColorEdit4("Third corner", m_Colors[2].elements);
}

} // namespace renderel::test
