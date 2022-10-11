#version 330 core

in vec2 v_Texture;

uniform sampler2D u_TexCrate;
uniform sampler2D u_TexFace;

out vec4 FragColor;

void main() {
  vec4 crateTexture = texture(u_TexCrate, v_Texture);
  vec4 faceTexture = texture(u_TexFace, v_Texture);

  // linearly interpolate between both textures (80% container, 20% awesomeface)
  FragColor = mix(crateTexture, faceTexture, 0.2);
}