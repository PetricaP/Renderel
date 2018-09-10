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
    virtual void *GetAPIwindow() = 0;

    virtual bool ShouldClose() const = 0;
    virtual void Clear() const = 0;
    virtual void SwapBuffers() const = 0;
    virtual void PollEvents() const = 0;

    void SetClearColor(float r, float g, float b) const;

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Width; }
};

} // namespace renderel

#endif // WINDOW_HPP
