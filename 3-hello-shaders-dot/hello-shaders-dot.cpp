#include <Engine.hpp>
using namespace std;

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
      GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);             // Create empty shader object
      glShaderSource(vertex_shader, 1, vertex_shader_source, 0);           // Hands shader source code to shader object
      glCompileShader(vertex_shader);                                      // Compiles source code in shader object

      // Create and compile fragment shader
      GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment_shader, 1, fragment_shader_source, 0);
      glCompileShader(fragment_shader);

      // Create program, attach shaders to it, link it
      rendering_program = glCreateProgram();                                 // Creates program object
      glAttachShader(rendering_program, vertex_shader);                      // Attach shader object to program object
      glAttachShader(rendering_program, fragment_shader);
      glLinkProgram(rendering_program);                                      // Links all shader objects attached to program together

      // Delete the shaders as the program has them now
      // shader objects not needed after linked into program object
      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);

      // NOTE This shows that the shader creation should be in a static function
      //rendering_program = compile_shaders();

      // Create a VAO
      // object that represents the vertex fetch stage of the OpenGL pipeline
      // used to supply input to the vertex shader
      // not used in this case as the vertex shader doesn't have any inputs atm
      // a VAO is still needed so OpenGL will let us draw
      glGenVertexArrays(1, &vertex_array_object);
      glBindVertexArray(vertex_array_object);
    }

    // Override Virtual Shutdown Function
    void shutdown() {
      // shader cleanup
      glDeleteVertexArrays(1, &vertex_array_object);
      glDeleteProgram(rendering_program);
      glDeleteVertexArrays(1, &vertex_array_object);
    }

    // Override Virtual Render Function
    void render(double currentTime) {
        const GLfloat green[] = { 0.0f, 0.25f, 0.0f,  1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

        // Use the program we created earlier for rendering
        glUseProgram(rendering_program);

        // Increase the point size
        glPointSize(40.0f);

        // DrawArrays sends vertices into the OpenGL pipeline
        // draws 1 point in this case
        glDrawArrays(GL_POINTS, 0, 1);
    }
};

DECLARE_MAIN(HelloShadersDot);
