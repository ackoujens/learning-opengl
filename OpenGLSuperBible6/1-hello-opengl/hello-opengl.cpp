#include <Engine.hpp>
#include <OpenGL/gl3.h>

class HelloOpengl : public Engine {

public:
    // Override Virtual Render Function
    void render(double currentTime) {
        //static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

        // void glClearBufferfv(GLenum buffer, GLint drawBuffer, const GLfloat *float);
        // -fv = accepts vector of floating point values
        // Tells OpenGL to clear the buffer specified by the first parameter
        // Second parameter is used when there are multiple output buffers to be cleared
        glClearBufferfv(GL_COLOR, 0, red);
    }

};

DECLARE_MAIN(HelloOpengl);
