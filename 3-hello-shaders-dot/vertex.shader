// Shader compiler version
// core indicates that we only use features from OpenGL core profile
#version 430 core

// Normal C program start point except in GLSL there are no parameters
void main(void) {
  // gl_Position is part of plumbing that connects the shader to the rest of OpenGL
  // represents output position of the vertex -> right in the middle of OpenGL clip space
  gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
}
