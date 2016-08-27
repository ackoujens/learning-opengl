#include <Engine.hpp>
#include <Vector>

/*
  Fragment shader is the last programmable stage in the pipeline
  Responsable for determining the color of each fragment before it's sent to framebuffer
  for possible composition into the window.

  After rasterizer processes a primitive, produces list of fragments
  that need to be colored and passes it to fragment shader.

  Explosion of work takes place here -> each triangle could produce 100s / 1000s / 1000000s fragments
*/

class FragmentShader2 : public Engine {
private:
    GLuint renderingProgram;
    GLuint vertexArrayObject;

public:
    // Check compilation for errors
    bool isShaderCompiled(GLuint shader) {
        GLint  isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the "NULL" character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

            // Provide the ingolog in whatever manor you deem best
            // Exit with failure
            glDeleteShader(shader);

            for(int i = 0; i<errorLog.size(); i++) {
                std::cout << errorLog[i];
            } std::cout << std::endl;

            return false;
        } else {
            // Shader compilation is successful
            return true;
        }
    }


    void startup() {
      // Source code for vertex shader
      static const GLchar * vertexShaderSource[] =
      {
        "#version 330 core                                                                      \n"
        // output that will be sent to the next shader stage
        "out vec4 vs_color; \n"
        "void main(void) {                                                                      \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),                       \n"
        "                                    vec4(-0.25, -0.25, 0.5, 1.0),                      \n"
        "                                    vec4(0.25, 0.25, 0.5, 1.0));                       \n"
        "   const vec4 colors[] = vec4[3](vec4(1.0, 0.0, 0.0, 1.0),                             \n"
        "                                 vec4(0.0, 1.0, 0.0, 1.0),                             \n"
        "                                 vec4(0.0, 0.0, 1.0, 1.0));                            \n"
        "                                                                                       \n"
        "   gl_Position = vertices[gl_VertexID];                                                \n"
        "   vs_color = colors[gl_VertexID]; \n"
        "}                                                                                      \n"
      };

      // Source code for fragment shader
      static const GLchar * fragmentShaderSource[] =
      {
        "#version 330 core                             \n"
        "in vec4 vs_color;                             \n"
        "out vec4 color;                               \n"
        "                                              \n"
        "void main(void) {                             \n"
        "   color = vs_color;                          \n"
        "}                                             \n"
      };

      // Create and compile vertex shader
      GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, vertexShaderSource, 0);
      glCompileShader(vertexShader);
      isShaderCompiled(vertexShader);

      // Create and compile fragment shader
      GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, fragmentShaderSource, 0);
      glCompileShader(fragmentShader);
      isShaderCompiled(fragmentShader);

      // Create program, attach shaders to it, link it
      renderingProgram = glCreateProgram();
      glAttachShader(renderingProgram, vertexShader);
      glAttachShader(renderingProgram, fragmentShader);
      glLinkProgram(renderingProgram);

      // Delete the shaders as the program has them now
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);

      // Create a VAO
      glGenVertexArrays(1, &vertexArrayObject);
      glBindVertexArray(vertexArrayObject);
    }

    // Override Virtual Shutdown Function
    void shutdown() {
      // Delete program object
      glDeleteVertexArrays(1, &vertexArrayObject);
      glDeleteProgram(renderingProgram);
      glDeleteVertexArrays(1, &vertexArrayObject);
    }

    // Override Virtual Render Function
    void render(double currentTime) {
        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f,  1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

        // Use the program we created earlier for rendering
        glUseProgram(renderingProgram);

        // Needed for anything to draw with the tesselation on
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

DECLARE_MAIN(FragmentShader2);
