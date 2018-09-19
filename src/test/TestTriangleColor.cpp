#include "test/TestTriangleColor.hpp"
#include <imgui.h>

namespace renderel::test {

TestTriangleColor::TestTriangleColor(const std::shared_ptr<Window> window)
	: Test(window), m_Colors{math::Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f),
							 math::Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f),
							 math::Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f)} {

	va = new graphics::VertexArray();

	vb = new graphics::VertexBuffer(m_Vertices, sizeof(m_Vertices));

	graphics::VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<int>(1);

	va->AddBuffer(vb, vbl);

	ib = new graphics::IndexBuffer<unsigned int>(
		m_Indices, sizeof(m_Indices) / sizeof(m_Indices[0]));

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
	ImGui::ColorEdit4("First corner", m_Colors[0].elements);
	ImGui::ColorEdit4("Second corner", m_Colors[1].elements);
	ImGui::ColorEdit4("Third corner", m_Colors[2].elements);
}

} // namespace renderel::test
