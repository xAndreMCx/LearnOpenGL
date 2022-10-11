#version 330 core

in vec2 v_Texture;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

out vec4 FragColor;

void main() {
  FragColor =
      mix(texture(u_Texture1, v_Texture), texture(u_Texture2, v_Texture), 0.2);
}