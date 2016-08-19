#include <Engine.hpp>
using namespace std;

/*
  Vertex shader is the only mandatory stage in the OpenGL pipeline
  Before the vertex shader runs -> fixed-function stage (vertex fetching / vertex pulling) is run
  -> provides inputs to vertex shader

  Getting data in and out in GLSL -> with global variables (in/out)
  in/out can be used as conduits between from shader to shader
  in variable in vertex shader is automatically filled in by fixed function vertex fetch stage
  -> vertex attribute
*/

class PipelinePassingData : public Engine {
private:
    GLuint rendering_program;
    GLuint vertex_array_object;

public:
    void startup() {
      // Source code for vertex shader
      static const GLchar * vertex_shader_source[] =
      {
        "#version 330 core                                                                      \n"
        "// offset is an input vertex attribute                                                 \n"
        "// layout is a layout qualifier used to set the location of the vertex attribute to 0  \n"
        "// this location is the value we'll pass in index to refer to the attribute            \n"
        "layout (location = 0) in vec4 offset;                                                  \n"
        "layout (location = 1) in vec4 color;                                                   \n"
        "                                                                                       \n"
        "// vs_color is an output that will be sent to the next shader stage                    \n"
        "out vec4 vs_color;                                                                     \n"
        "                                                                                       \n"
        "void main(void) {                                                                      \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),                       \n"
        "                                    vec4(-0.25, -0.25, 0.5, 1.0),                      \n"
        "                                    vec4(0.25, 0.25, 0.5, 1.0));                       \n"
        "// Add offset to our hard-coded vertex position                                        \n"
        "   gl_Position = vertices[gl_VertexID] + offset;                                       \n"
        "vs_color = color;                                                                      \n"
        "}                                                                                      \n"
      };

      // Source code for fragment shader
      static const GLchar * fragment_shader_source[] =
      {
        "#version 330 core                            \n"
        "                                             \n"
        "// Input from the vertex shader              \n"
        "in vec4 vs_color;                            \n"
        "out vec4 color;                              \n"
        "                                             \n"
        "void main(void) {                            \n"
        "   color = vs_color;                         \n"
        "}                                            \n"
      };

      // Create and compile vertex shader
      GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex_shader, 1, vertex_shader_source, 0);
      glCompileShader(vertex_shader);

      // Create and compile fragment shader
      GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment_shader, 1, fragment_shader_source, 0);
      glCompileShader(fragment_shader);

      // Create program, attach shaders to it, link it
      rendering_program = glCreateProgram();
      glAttachShader(rendering_program, vertex_shader);
      glAttachShader(rendering_program, fragment_shader);
      glLinkProgram(rendering_program);

      // Delete the shaders as the program has them now
      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);

      // Create a VAO
      glGenVertexArrays(1, &vertex_array_object);
      glBindVertexArray(vertex_array_object);
    }

    // Override Virtual Shutdown Function
    void shutdown() {
      // Delete program object
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

        GLfloat attrib[] = { (float)sin(currentTime) * 0.5f,
                             (float)cos(currentTime) * 0.6f,
                             0.0f, 0.0f };

        // Update the value of input attribute 0
        // Parameter index is used to reference the attribute
        // v is a pointer to the new data to put into the attribute

        // Each time glVertexAttrib is called it will update the value
        // of the vertex attribute that is passed to the vertex shader
        glVertexAttrib4fv(0, attrib);

        // Draw one triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

DECLARE_MAIN(PipelinePassingData);
