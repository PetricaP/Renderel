#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "math/Mat4.hpp"
#include "math/Vec3.hpp"

namespace renderel {

class Camera {
  private:
	math::Mat4<> m_Perspective;
	math::Vec3<> m_Position;
	math::Vec3<> m_Forward;
	math::Vec3<> m_Up;

  public:
	Camera(const math::Vec3<> &position, float fov, float aspectRatio,
		   float zNear, float zFar)
		: m_Perspective(
			  math::Mat4<>::Perspective(fov, aspectRatio, zNear, zFar)),
		  m_Position(position), m_Forward(math::Vec3<>(0.0f, 0.0f, 1.0f)),
		  m_Up(math::Vec3<>(0.0f, 1.0f, 0.0f)) {}

	math::Mat4<> GetView() const {
		return math::Mat4<>::LookAt(m_Position, m_Position + m_Forward, m_Up);
	}

	void SetUp(math::Vec3<> &up) { m_Up = up; }
	math::Vec3<> GetUp() { return m_Up; }

	void SetForward(const math::Vec3<> &forward) { m_Forward = forward; }
	math::Vec3<> GetForward() { return m_Forward; }

	void SetPosition(const math::Vec3<> &position) { m_Position = position; }
	math::Vec3<> GetPosition() { return m_Position; }

	math::Mat4<> GetProjection() const { return m_Perspective; }
};

} // namespace renderel

#endif // CAMERA_HPP
