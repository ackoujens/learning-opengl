#include <Engine.hpp>
#include <Vector>

/*
  Compute shader available from OpenGL Version 4.3
  (Not available on my macbook and so not able to debug this code)
*/

class ComputeShader : public Engine {
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

      // Source code for compute shader
      static const GLchar * computeShaderSource[] =
      {
        "#version 430 core                                  \n"
        // Tells OpenGL that the size of the local workgroup is going to be 32 x 32
        "layout (local_size_x = 32, local_size_y = 32) in;  \n"
        "                                                   \n"
        "void main(void) {                                  \n"
        "   // DO NOTHING                                   \n"
        "}                                                  \n"
      };

      // Create and compile fragment shader
      GLuint computeShader = glCreate(GL_COMPUTE_SHADER);
      glShaderSource(computeShader, 1, computeShaderSource, 0);
      glCompileShader(computeShader);
      isShaderCompiled(computeShader);

      // Create program, attach shaders to it, link it
      renderingProgram = glCreateProgram();
      glAttachShader(renderingProgram, computeShader);
      glLinkProgram(renderingProgram);

      // Delete the shaders as the program has them now
      glDeleteShader(computeShader);

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

DECLARE_MAIN(ComputeShader);
