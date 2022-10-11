#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexture;

out vec2 v_Texture;

uniform mat4 u_MVP;

void main() {
  gl_Position = u_MVP * vec4(aPos.xyz, 1.0);
  v_Texture = aTexture;
}