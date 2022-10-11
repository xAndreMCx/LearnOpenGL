#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec3 i_Normal;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
// uniform mat4 u_NormalMatrix;

out vec3 Normal;
out vec3 FragPosition;

void main() {
  mat4 MVP = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix;
  FragPosition = vec3(u_ModelMatrix * vec4(i_Position, 1.0));
  gl_Position = MVP * vec4(i_Position, 1.0);
  // Normal = mat3(u_NormalMatrix) * i_Normal; used if there's non uniform
  // scaling
  Normal = i_Normal;
}