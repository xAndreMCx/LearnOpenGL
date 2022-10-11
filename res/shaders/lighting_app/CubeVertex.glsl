#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec3 i_Normal;
layout(location = 2) in vec2 i_Texture;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec3 Normal;
out vec2 TextureCoords;
out vec3 FragPosition;

void main() {
  mat4 MVP = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix;

  FragPosition = vec3(u_ModelMatrix * vec4(i_Position, 1.0));

  gl_Position = MVP * vec4(i_Position, 1.0);

  TextureCoords = i_Texture;
  Normal = i_Normal;
}