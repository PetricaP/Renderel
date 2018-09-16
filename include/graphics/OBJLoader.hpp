#ifndef GRAPHICS_OBJLOADER_HPP
#define GRAPHICS_OBJLOADER_HPP

#include "graphics/IndexBuffer.hpp"
#include "graphics/VertexArray.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#define VERTEX "v"
#define TEXTURE "vt"
#define NORMAL "vn"
#define FACE "f"

#define VERTICES_PER_FACE 3

namespace renderel::graphics::OBJLoader {

template <typename U = float>
struct Vertex {
	math::Vec3<U> position;
	math::Vec2<U> texCoords;
	// TODO: math::Vec3<T> normal;
	bool operator==(const Vertex &other) const;
};

template <typename U = float>
bool Vertex<U>::operator==(const Vertex<U> &other) const {
	// TODO: Vec2, Vec3, Vec4 operator==
	return this->position.x == other.position.x &&
		   this->position.y == other.position.y &&
		   this->position.z == other.position.z &&
		   this->texCoords.u == other.texCoords.u &&
		   this->texCoords.v == other.texCoords.v;
}

/*
 * T - IndexBuffer data type - defaults to unsigned int
 * U - Vertex data type - defaults to float
 */
template <typename T = unsigned int, typename U = float>
bool Load(const std::string &path, IndexBuffer<T> *&ib, VertexArray *&va) {

	std::vector<math::Vec3<U>> vertexPositions;
	std::vector<math::Vec2<U>> textures;
	std::vector<math::Vec3<U>> normals;

	std::vector<Vertex<U>> vertices;
	std::vector<T> indices;

	FILE *objFile = fopen(path.c_str(), "rt");
	if (objFile == nullptr) {
		fprintf(stderr, "Couldn't open file %s\n", path.c_str());
		return false;
	}

	char begin[128];

	int currentLine = 0;

	while (fscanf(objFile, "%s", begin) != EOF) {
		if (strcmp(begin, VERTEX) == 0) {
			math::Vec3<> position;
			fscanf(objFile, "%f %f %f\n", &position.x, &position.y,
				   &position.z);
			vertexPositions.push_back(position);
		} else if (strcmp(begin, FACE) == 0) {
			math::Vec3<unsigned int> vertIndex;
			math::Vec3<unsigned int> texCoordIndex;
			math::Vec3<unsigned int> normalIndex;
			for (unsigned int i = 0; i < VERTICES_PER_FACE; ++i) {
				fscanf(objFile, "%u/%u/%u ", &vertIndex[i], &texCoordIndex[i],
					   &normalIndex[i]);

				// Create a vertex
				Vertex v;
				v.position = vertexPositions[vertIndex[i] - 1];
				v.texCoords = textures[texCoordIndex[i] - 1];

				// Check if it already exists
				auto position = std::find(vertices.begin(), vertices.end(), v);

				// Add it if needed, and add index to it
				if (position == vertices.end()) {
					vertices.push_back(v);
					indices.push_back(vertices.size() - 1);
				} else {
					T pos = (T)(position - vertices.begin());
					indices.push_back(pos);
				}
			}
			// BECAUSE OBJ INDEXES START FROM  !!!!!!!!!!!!!!!111!!!!1!!!!!!
		} else if (strcmp(begin, TEXTURE) == 0) {
			math::Vec2<> coord;
			fscanf(objFile, "%f %f\n", &coord.x, &coord.y);
			textures.push_back(coord);
		} else if (strcmp(begin, NORMAL) == 0) {
			math::Vec3<> coord;
			fscanf(objFile, "%f %f %f\n", &coord.x, &coord.y, &coord.z);
			normals.push_back(coord);
		}
		++currentLine;
	}

	va = new VertexArray();

	VertexBuffer *vb = new VertexBuffer(
		vertices.data(),
		static_cast<unsigned int>(vertices.size() * sizeof(Vertex<U>)));

	VertexBufferLayout vbl;
	vbl.Push<U>(3);
	vbl.Push<U>(2);

	va->AddBuffer(vb, vbl);

	ib = new IndexBuffer<T>(
		indices.data(), static_cast<unsigned int>(
							indices.size()));
	fclose(objFile);

	return true;
}

} // namespace renderel::graphics::OBJLoader

#endif // GRAPHICS_OBJLOADER_HPP
