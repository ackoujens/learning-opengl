// NOTE Seperate shader files not in use ATM
// Shader compiler version
// core indicates that we only use features from OpenGL core profile
#version 330 core

// OUTPUT variable color will be sent to the window or screen
out vec4 color;

void main(void) {
  // Cyan color
  color = vec4(0.0, 1.0, 1.0, 1.0);
}
