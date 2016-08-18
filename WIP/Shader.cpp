//
//  Shader.cpp
//  Compile shaders and link them together into a program

#include <Shader.hpp>

GLuint compile_shaders(void) {
  // Source code for vertex shader
  static const GLchar * vertex_shader_source[] =
  {
    "#version 430 core                            \n"
    "                                             \n"
    "void main(void) {                            \n"
    "   gl_Position = vec4(0.0, 0.0, 0.5, 1.0);   \n"
    "}                                            \n"
  };

  // Source code for fragment shader
  static const GLchar * fragment_shader_source[] =
  {
    "#version 430 core                            \n"
    "                                             \n"
    "out vec4 color;                              \n"
    "                                             \n"
    "void main(void) {                            \n"
    "   color = vec4(0.0, 0.8, 1.0, 1.0);         \n"
    "}                                            \n"
  };

  // Create and compile vertex shader
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);                    // Create empty shader object
  glShaderSource(vertex_shader, 1, vertex_shader_source, 0);           // Hands shader source code to shader object
  glCompileShader(vertex_shader);                                      // Compiles source code in shader object

  // Create and compile fragment shader
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, fragment_shader_source, 0);
  glCompileShader(fragment_shader);

  // Create program, attach shaders to it, link it
  GLuint program = glCreateProgram();                                              // Creates program object
  glAttachShader(program, vertex_shader);                                   // Attach shader object to program object
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);                                                   // Links all shader objects attached to program together

  // Delete the shaders as the program has them now
  glDeleteShader(vertex_shader);                                            // Shader objects not needed anymore after they are linked into program object
  glDeleteShader(fragment_shader);

  // Need to keep the program object so we can use it to draw things
  // Stored on application startup so we don't need to recompile
  // the shader every time we want to use it -> startup()
  return program;
}
