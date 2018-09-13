#ifndef GRAPHICS_OBJLOADER_HPP
#define GRAPHICS_OBJLOADER_HPP

#include "graphics/IndexBuffer.hpp"
#include "graphics/VertexArray.hpp"

namespace renderel::graphics {

namespace OBJLoader {

bool Load(const std::string &path, IndexBuffer *&ib, VertexArray *&va);

}

} // namespace renderel::graphics

#endif // GRAPHICS_OBJLOADER_HPP
