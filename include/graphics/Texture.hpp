#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "core/Common.hpp"
#include <string>

namespace renderel::graphics {

class Texture {
  private:
	std::string m_FilePath;
	uint32 m_RendererID = 0;
	uint8 *m_LocalBuffer = nullptr;
	int32 m_Width = 0;
	int32 m_Height = 0;
	int32 m_BPP = 0;

  public:
	Texture(const std::string &path);
	~Texture();

	void Bind(uint32 slot = 0) const;
	void Unbind() const;

	int32 GetWidth() const { return m_Width; }
	int32 GetHeight() const { return m_Height; }
};

} // namespace renderel::graphics

#endif // TEXTURE_HPP
