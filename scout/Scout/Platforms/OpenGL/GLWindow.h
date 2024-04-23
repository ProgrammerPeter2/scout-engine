#include "../../Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Scout {
class GLWindow: public Window {
    public:
        explicit GLWindow(WindowProps props);

        void close() override;
        void render() override;
    private:
        GLFWwindow *window;
        char* title;
    };
}