#include <Engine.hpp>

class PipelineVertexAttributes : public Engine {
private:
    GLuint renderingProgram;
    GLuint vertexArrayObject;

public:
    // Override Virtual Startup Function
    void startup() {
      // Source code for vertex shader
      static const GLchar * vertexShaderSource[] =
      {
        "#version 330 core                                                \n"
        "// offset is an input vertex attribute                           \n"
        "layout (location = 0) in vec4 offset;                            \n"
        "                                                                 \n"
        "void main(void) {                                                \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0), \n"
        "                                    vec4(-0.25, -0.25, 0.5, 1.0),\n"
        "                                    vec4(0.25, 0.25, 0.5, 1.0)); \n"
        "// Add offset to our hard-coded vertex position                  \n"
        "   gl_Position = vertices[gl_VertexID] + offset;                 \n"
        "}                                                                \n"
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
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);

      // Create a VAO
      // Object that represents the vertex fetch stage of the OpenGL pipeline
      // used to supply input to the vertex vertex shader
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

        GLfloat attrib[] = { (float)sin(currentTime) * 0.5f,
                             (float)cos(currentTime) * 0.6f,
                              0.0f, 0.0f };

        // Update the value of input attribute 0 in the vertex shader
        glVertexAttrib4fv(0, attrib);

        // Draw one triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

DECLARE_MAIN(PipelineVertexAttributes);
