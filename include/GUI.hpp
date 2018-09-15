#ifndef GUI_HPP
#define GUI_HPP

#include <string>

namespace renderel {

class GUI {
  public:
	virtual ~GUI() = default;
	virtual void Init() = 0;
	virtual void Begin(const std::string &name) = 0;
	virtual void End() = 0;
	virtual void Render() = 0;
	virtual bool Button(const std::string &name) = 0;
};

} // namespace renderel

#endif // GUI_HPP
