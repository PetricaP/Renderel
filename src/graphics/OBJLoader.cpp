#include "graphics/OBJLoader.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "math/Vec2.hpp"
#include "math/Vec3.hpp"

#define VERTEX  "v"
#define TEXTURE "vt"
#define NORMAL  "vn"
#define FACE    "f"

namespace renderel::graphics {

bool OBJLoader::Load(const std::string &path, IndexBuffer *&ib,
					 VertexArray *&va) {

	std::vector<math::Vec3<>> vertices;
	std::vector<math::Vec2<>> textures;
	std::vector<math::Vec3<>> normals;
	std::vector<math::Vec3<unsigned int>> indices;

	FILE *objFile = fopen(path.c_str(), "rt");
	if (objFile == nullptr) {
		fprintf(stderr, "Couldn't open file %s\n", path.c_str());
		return false;
	}

	char begin[32];

	int currentLine = 0;

	while (fscanf(objFile, "%s", begin) != EOF) {
		if (strcmp(begin, VERTEX) == 0) {
			math::Vec3<> position;
			fscanf(objFile, "%f %f %f\n", &position.x, &position.y,
				   &position.z);
			vertices.push_back(position);
		} else if (strcmp(begin, FACE) == 0) {
			math::Vec3<unsigned int> vert;
			math::Vec3<unsigned int> texCoord;
			math::Vec3<unsigned int> normal;
			for (unsigned int i = 0; i < 3; ++i) {
				fscanf(objFile, "%u/%u/%u ", &vert[i], &texCoord[i],
					   &normal[i]);
			}
			// BECAUSE OBJ INDEXES START FROM  !!!!!!!!!!!!!!!111!!!!1!!!!!!
			vert -= 1;
			indices.push_back(vert);
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

	VertexBuffer vb(
		vertices.data(),
		static_cast<unsigned int>(vertices.size() * sizeof(math::Vec3<>)));

	VertexBufferLayout vbl;
	vbl.Push<float>(3);

	va->AddBuffer(vb, vbl);

	ib = new IndexBuffer(indices.data(),
						 static_cast<unsigned int>(
							 indices.size() * sizeof(math::Vec3<unsigned int>) /
							 sizeof(unsigned int)));
	fclose(objFile);

	return true;
}

} // namespace renderel::graphics
