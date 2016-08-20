#include <Engine.hpp>
#include <Vector>

/*
  Tessellation: process of breaking a high-order primitive (a patch)
  into many smaller, simpler primitives (triangles) for rendering.

  OpenGL includes fixed-function configurable tessellation engine
  =  able to break up: quadrilaterals, triangles, lines
   -> large number of: triangles, lines, smaller points

  Can be directly consumed by the normal rasterization hardware further down pipeline

  Tessellation phase sits directly after vertex shading stage, made up out 3 parts:
  -> tessellation control shader, fixed-function tessellation engine, tessellation evaluation shader
*/

class TessellationControlShader : public Engine {
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
        "void main(void) {                                                                      \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),                       \n"
        "                                    vec4(-0.25, -0.25, 0.5, 1.0),                      \n"
        "                                    vec4(0.25, 0.25, 0.5, 1.0));                       \n"
        "                                                                                       \n"
        "   // Add offset to our hard-coded vertex position                                     \n"
        "   gl_Position = vertices[gl_VertexID];                                                \n"
        "}                                                                                      \n"
      };

      // Source code tessellation control shader
      static const GLchar * tessellationControlShaderSource[] =
      {
        "#version 330 core                                                              \n"
        "layout (vertices = 3) out;                                                     \n"
        "                                                                               \n"
        "void main(void) {                                                              \n"
        "   if(gl_InvocationID == 0) {                                                  \n"
        "       gl_TessLevelInner[0] = 5.0;                                              \n"
        "       gl_TessLevelOuter[0] = 5.0;                                              \n"
        "       gl_TessLevelOuter[1] = 5.0;                                              \n"
        "       gl_TessLevelOuter[2] = 5.0;                                              \n"
        "   }                                                                           \n"
        "   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;   \n"
        "}                                                                              \n"
      };

      // Source code tessellation evaluation shader
      static const GLchar * tessellationEvaluationShaderSource[] =
      {
        "#version 330 core                                              \n"
        "layout (triangles, equal_spacing, cw) in;                      \n"
        "                                                               \n"
        "void main(void) {                                              \n"
        "   gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +      \n"
        "                  (gl_TessCoord.y * gl_in[1].gl_Position) +      \n"
        "                  (gl_TessCoord.z * gl_in[2].gl_Position);      \n"
        "}                                                              \n"
      };

      // Source code for fragment shader
      static const GLchar * fragmentShaderSource[] =
      {
        "#version 330 core                             \n"
        // NOTE Forgot to put "out" here and stared blindly at my screen
        // because I couldn't figure out why nothing was drawing without any errors
        "out vec4 color;                                   \n"
        "                                              \n"
        "void main(void) {                             \n"
        "   color = vec4(0.0, 1.0, 1.0, 1.0);          \n"
        "}                                             \n"
      };



      // Create and compile vertex shader
      GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, vertexShaderSource, 0);
      glCompileShader(vertexShader);
      isShaderCompiled(vertexShader);

      // Create and compile tessellation control shader
      GLuint tessellationControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
      glShaderSource(tessellationControlShader, 1, tessellationControlShaderSource, 0);
      glCompileShader(tessellationControlShader);
      isShaderCompiled(tessellationControlShader);

      // Create and compile tessellation evaluation shader
      GLuint tessellationEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
      glShaderSource(tessellationEvaluationShader, 1, tessellationEvaluationShaderSource, 0);
      glCompileShader(tessellationEvaluationShader);
      isShaderCompiled(tessellationEvaluationShader);

      // Create and compile fragment shader
      GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, fragmentShaderSource, 0);
      glCompileShader(fragmentShader);
      isShaderCompiled(fragmentShader);

      // Create program, attach shaders to it, link it
      renderingProgram = glCreateProgram();
      glAttachShader(renderingProgram, vertexShader);
      glAttachShader(renderingProgram, tessellationControlShader);
      glAttachShader(renderingProgram, tessellationEvaluationShader);
      glAttachShader(renderingProgram, fragmentShader);
      glLinkProgram(renderingProgram);

      // Delete the shaders as the program has them now
      glDeleteShader(vertexShader);
      glDeleteShader(tessellationControlShader);
      glDeleteShader(tessellationEvaluationShader);
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

        // Draw one triangle
        // Enable wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Needed for anything to draw with the tesselation on
        glDrawArrays(GL_PATCHES, 0, 3);
    }
};

DECLARE_MAIN(TessellationControlShader);
