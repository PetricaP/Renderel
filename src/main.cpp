#include "Window.hpp"
#include "GL/glew.h"
#include <iostream>

int main() {
    renderel::graphics::Window window(960, 540, "Hello");
    window.setClearColor(0.7f, 0.2f, 0.2f);
	while (!window.ShouldClose()) {
        window.PollEvents();
        window.Clear();
	}
}
