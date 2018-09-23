#ifndef GRAPHICS_OBJLOADER_HPP
#define GRAPHICS_OBJLOADER_HPP

#include "graphics/Vertex.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include <algorithm>
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

using math::Vec2;
using math::Vec3;
using std::string;
using std::vector;

/*
 * T - IndexBuffer data type - defaults to unsigned int
 * U - Vertex data type - defaults to float
 */
template <typename T = unsigned int, typename U = float>
bool Load(const string &path, std::vector<Vertex<U>> &vertices,
		  vector<T> &indices, bool loadTextures = false,
		  bool loadNormals = false) {

	vector<Vec3<U>> vertexPositions;
	vector<Vec2<U>> textures;
	vector<Vec3<U>> normals;

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
				Vertex<U> v;
				v.position = vertexPositions[vertIndex[i] - 1];

				if (loadTextures) {
					v.texCoords = textures[texCoordIndex[i] - 1];
				} else {
					v.texCoords = Vec2<U>(0.0f, 0.0f);
				}
				if (loadNormals) {
					v.normal = normals[normalIndex[i] - 1];
				} else {
					v.normal = Vec3<U>(0.0f, 0.0f, 0.0f);
				}

				// Check if it already exists
				auto position = std::find(vertices.begin(), vertices.end(), v);

				// Add it if needed, and add index to it
				if (position == vertices.end()) {
					vertices.push_back(v);
					indices.push_back(vertices.size() - 1);
				} else {
					T pos = static_cast<T>(position - vertices.begin());
					indices.push_back(pos);
				}
			}
		} else if (loadTextures && strcmp(begin, TEXTURE) == 0) {
			math::Vec2<> coord;
			fscanf(objFile, "%f %f\n", &coord.x, &coord.y);
			textures.push_back(coord);
		} else if (loadNormals && strcmp(begin, NORMAL) == 0) {
			math::Vec3<> coord;
			fscanf(objFile, "%f %f %f\n", &coord.x, &coord.y, &coord.z);
			normals.push_back(coord);
		}
		++currentLine;
	}

	fclose(objFile);

	return true;
} // namespace renderel::graphics::OBJLoader

template <typename T, typename U>
bool computeTangents(vector<Vertex<U>> &vertices, vector<T> &indices) {

	for (unsigned int i = 0; i < vertices.size(); ++i) {
		// TODO separate verts even if they have the same coords
	}

	return true;
}

} // namespace renderel::graphics::OBJLoader

#endif // GRAPHICS_OBJLOADER_HPP
