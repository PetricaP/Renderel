#ifndef MESH_HPP
#define MESH_HPP

#include "math/Vec3.hpp"

namespace renderel::renderel {

class Vertex {
  private:
    math::Vec3<> m_Position;

  public:
    Vertex(const math::Vec3<> position) : m_Position(position) {}
};

class Mesh {
  public:
  private:
};

} // namespace renderel::renderel

#endif // MESH_HPP
