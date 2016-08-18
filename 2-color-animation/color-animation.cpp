#include <Engine.hpp>
#include <OpenGL/gl3.h>
#include <Math.h>
using namespace std;

class my_application : public Engine {
public:

    // Override Virtual Render Function
    void render(double currentTime) {
        // Multiply color values with currenTime for a simple animation
        const GLfloat red[] = { (float)sin(currentTime) * 0.5f + 0.5f,
                                       (float)cos(currentTime) * 0.5f + 0.5f,
                                       0.0f, 1.0f };

        glClearBufferfv(GL_COLOR, 0, red);
    }
};

DECLARE_MAIN(my_application);
