#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"
#include "math/Vec3.hpp"

namespace renderel {

template <typename T = float>
class Transform {
  private:
	math::Vec3<T> m_Position;
	math::Quaternion<T> m_Rotation;
	math::Vec3<T> m_Scale;

  public:
	Transform()
		: m_Position(0.0f), m_Rotation(1.0f, 0.0f, 0.0f, 0.0f), m_Scale(1.0f) {}

	Transform(const math::Vec3<T> &position = math::Vec3<T>(),
			  const math::Quaternion<T> &rotation = math::Quaternion<T>(),
			  const math::Vec3<T> &scale = math::Vec3<T>(1.0f))
		: m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

	math::Mat4<T> GetModel() const {
		math::Mat4<T> positionMatrix = math::Mat4<T>::Translation(m_Position);
		math::Mat4<T> scaleMatrix = math::Mat4<T>::Scale(m_Scale);
		math::Mat4<T> rotationMatrix = m_Rotation.ToRotationMatrix();
		return positionMatrix * rotationMatrix * scaleMatrix;
	}

	math::Vec3<T> &GetPosition() { return m_Position; }
	math::Quaternion<T> &GetRotation() { return m_Rotation; }
	math::Vec3<T> &GetScale() { return m_Scale; }

	void SetPosition(const math::Vec3<T> position) { m_Position = position; }
	void SetRotation(const math::Quaternion<T> rotation) {
		m_Rotation = rotation;
	}
	void SetScale(const math::Vec3<T> scale) { m_Scale = scale; }
};

} // namespace renderel

#endif // TRANSFORM_HPP
