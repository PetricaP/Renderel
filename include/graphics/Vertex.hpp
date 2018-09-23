#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include <vector>

namespace renderel::graphics {

using math::Vec2;
using math::Vec3;
using std::string;
using std::vector;

template <typename U = float>
struct Vertex {
	Vec3<U> position;
	Vec2<U> texCoords;
	Vec3<U> normal;
	Vec3<U> tangent;
	Vec3<U> bitangent;

	bool operator==(const Vertex &other) const;
};

template <typename U>
bool Vertex<U>::operator==(const Vertex<U> &other) const {
	return position == other.position && texCoords == other.texCoords &&
		   normal == other.normal;
	// If normal is the same, tangent and bitangent doesn't matter because they
	// are computed from normal
}

} // namespace renderel::graphics

#endif // !VERTEX_HPP
