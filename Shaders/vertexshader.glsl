#version 330 core

layout(location = 0) in vec3 vertexPos;// ����� VAO

void main() {
  gl_Position.xyz = vertexPos;
  gl_Position.w = 1.0;
}