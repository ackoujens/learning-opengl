#include <Engine.hpp>

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
    void startup() {
      // Source code for vertex shader
      static const GLchar * vertexShaderSource[] =
      {
        "#version 330 core                                                                      \n"
        "// offset is an input vertex attribute                                                 \n"
        "// layout is a layout qualifier used to set the location of the vertex attribute to 0  \n"
        "// this location is the value we'll pass in index to refer to the attribute            \n"
        "layout (location = 0) in vec4 offset;                                                  \n"
        "layout (location = 1) in vec4 color;                                                   \n"
        "                                                                                       \n"
        "// Declare VS_OUT as an output interface block                                         \n"
        "out VS_OUT {                                                                           \n"
        "   vec4 color;                                                                         \n"
        "} vs_out; \n"
        "                                                                                       \n"
        "void main(void) {                                                                      \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),                       \n"
        "                                    vec4(-0.25, -0.25, 0.5, 1.0),                      \n"
        "                                    vec4(0.25, 0.25, 0.5, 1.0));                       \n"
        "   // Add offset to our hard-coded vertex position                                     \n"
        "   gl_Position = vertices[gl_VertexID] + offset;                                       \n"
        "                                                                                       \n"
        "   // Output a fixed value for vs_color                                                \n"
        "   vs_out.color = color;                                                               \n"
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
        "       glTessLevelInner[0] = 5.0;                                              \n"
        "       glTessLevelOuter[0] = 5.0;                                              \n"
        "       glTessLevelOuter[1] = 5.0;                                              \n"
        "       glTessLevelOuter[2] = 5.0;                                              \n"
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
        "   gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +      \n"
        "                  gl_TessCoord.y * gl_in[1].gl_Position +      \n"
        "                  gl_TessCoord.z * gl_in[2].gl_Position);      \n"
        "}                                                              \n"
      };

      // Source code for fragment shader
      static const GLchar * fragmentShaderSource[] =
      {
        "#version 330 core                             \n"
        "// Declare VS_OUT as an input interface block \n"
        "in VS_OUT {                                   \n"
        "   vec4 color;                                \n"
        "} fs_in;                                      \n"
        "                                              \n"
        "out vec4 color;                               \n"
        "                                              \n"
        "void main(void) {                             \n"
        "   color = fs_in.color;                       \n"
        "}                                             \n"
      };

      // Create and compile vertex shader
      GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, vertexShaderSource, 0);
      glCompileShader(vertexShader);
        
        // Create and compile tessellation control shader
        GLuint tessellationControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tessellationControlShader, 1, tessellationControlShaderSource, 0);
        glCompileShader(tessellationControlShader);
        
        // Create and compile tessellation evaluation shader
        GLuint tessellationEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tessellationEvaluationShader, 1, tessellationEvaluationShaderSource, 0);
        glCompileShader(tessellationEvaluationShader);

      // Create and compile fragment shader
      GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, fragmentShaderSource, 0);
      glCompileShader(fragmentShader);

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
        const GLfloat green[] = { 0.0f, 0.25f, 0.0f,  1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

        // Use the program we created earlier for rendering
        glUseProgram(renderingProgram);

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
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

DECLARE_MAIN(TessellationControlShader);
