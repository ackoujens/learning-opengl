#include <Engine.hpp>

/*
  OpenGL works by connecting a number of mini-programs called shaders together with fixed-function-glue.
  GFX Processor executes your shaders when you draw -> pipes in&outputs along the pipeline
  until pixels come out the end.

  OpenGL shaders are written in C based GLSL
  Compiler is built into OpenGL <- shader objects
  Multiple shaders get linked together -> program object
  Each program object can contain shaders for 1 or more shader stages.

  Shader stages of OpenGL:
  - vertex shaders
  - tesselation control
  - evaluation shaders
  - geometry shaders
  - fragment shaders
  - compute shaders

  Minimal setup for a visual result:
  - vertex shader
  - fragment shader
*/

class HelloShadersDot : public Engine {
private:
    GLuint renderingProgram;
    GLuint vertexArrayObject;

public:
    // Override Virtual Startup Function
    void startup() {
      // Source code for vertex shader
      // NOTE had an issue with version 430 core
      // changing it to 330 solved the issue of OpenGL not drawing my point
      static const GLchar * vertexShaderSource[] =
      {
        "#version 330 core                            \n"
        "void main(void) {                            \n"
        "   gl_Position = vec4(0.0, 0.0, 0.5, 1.0);   \n"
        "}                                            \n"
      };

      // Source code for fragment shader
      static const GLchar * fragmentShaderSource[] =
      {
        "#version 330 core                            \n"
        "                                             \n"
        "out vec4 color;                              \n"
        "                                             \n"
        "void main(void) {                            \n"
        "   color = vec4(0.0, 1.0, 1.0, 1.0);         \n"
        "}                                            \n"
      };

      // Create and compile vertex shader
      GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);             // Create empty shader object
      glShaderSource(vertexShader, 1, vertexShaderSource, 0);           // Hands shader source code to shader object
      glCompileShader(vertexShader);                                      // Compiles source code in shader object

      // Create and compile fragment shader
      GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, fragmentShaderSource, 0);
      glCompileShader(fragmentShader);

      // Create program, attach shaders to it, link it
      renderingProgram = glCreateProgram();                                 // Creates program object
      glAttachShader(renderingProgram, vertexShader);                      // Attach shader object to program object
      glAttachShader(renderingProgram, fragmentShader);
      glLinkProgram(renderingProgram);                                      // Links all shader objects attached to program together

      // Delete the shaders as the program has them now
      // shader objects not needed after linked into program object
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);

      // NOTE This shows that the shader creation should be in a static function
      //rendering_program = compile_shaders();

      // Create a VAO
      // object that represents the vertex fetch stage of the OpenGL pipeline
      // used to supply input to the vertex shader
      // not used in this case as the vertex shader doesn't have any inputs atm
      // a VAO is still needed so OpenGL will let us draw
      glGenVertexArrays(1, &vertexArrayObject);
      glBindVertexArray(vertexArrayObject);
    }

    // Override Virtual Shutdown Function
    void shutdown() {
      // shader cleanup
      glDeleteVertexArrays(1, &vertexArrayObject);
      glDeleteProgram(renderingProgram);
      glDeleteVertexArrays(1, &vertexArrayObject);
    }

    // Override Virtual Render Function
    void render(double currentTime) {
        const GLfloat green[] = { 0.0f, 0.25f, 0.0f,  1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

        // Use the program we created earlier for rendering
        glUseProgram(renderingProgram);

        // Increase the point size
        glPointSize(40.0f);

        // DrawArrays sends vertices into the OpenGL pipeline
        // draws 1 point in this case
        glDrawArrays(GL_POINTS, 0, 1);
    }
};

DECLARE_MAIN(HelloShadersDot);
