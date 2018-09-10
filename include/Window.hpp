#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

namespace renderel {

class Window {
  private:
	int m_Width;
	int m_Height;

  protected:
    Window(int width, int height);

  public:
    virtual ~Window() = default;

    // This method is only here for debugging
    virtual void *GetAPIWindowHandle() = 0;

    virtual bool ShouldClose() const = 0;
    virtual void SwapBuffers() const = 0;
    virtual void PollEvents() const = 0;

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Width; }
};

} // namespace renderel

#endif // WINDOW_HPP
