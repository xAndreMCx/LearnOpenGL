#version 330 core
 
layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec2 i_TextureCoords;

uniform mat4 u_Transform;

out vec2 v_Texture;

void main() {
    gl_Position = u_Transform * vec4(i_Position.xyz, 1.0);
    v_Texture = i_TextureCoords;

 }