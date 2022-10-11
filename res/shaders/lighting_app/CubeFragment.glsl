#version 330 core

struct Material {
  sampler2D Diffuse;
  sampler2D Specular;
  float Shininess;
};

struct Light {
  vec3 Position;
  vec3 Color;
  vec3 Ambient;
  vec3 Diffuse;
  vec3 Specular;
};

in vec3 Normal;
in vec2 TextureCoords;
in vec3 FragPosition;

uniform vec3 u_CameraPosition;
uniform Material u_Material;
uniform Light u_Light;

out vec4 FragColor;

void main() {
  // Ambient
  vec3 ambient = u_Light.Ambient *
                 vec3(texture(u_Material.Diffuse, TextureCoords)) *
                 u_Light.Color;

  // Diffuse
  vec3 NormalizedNormal = normalize(Normal);
  vec3 LightDirection = normalize(u_Light.Position - FragPosition);
  float Difference = max(dot(NormalizedNormal, LightDirection), 0.0);
  vec3 diffuse = u_Light.Diffuse * Difference *
                 vec3(texture(u_Material.Diffuse, TextureCoords)) *
                 u_Light.Color;

  // Specular
  vec3 ViewDirection = normalize(u_CameraPosition - FragPosition);
  vec3 ReflectDirection = reflect(-LightDirection, NormalizedNormal);
  float spec = (pow(max(dot(ViewDirection, ReflectDirection), 0.0),
                    u_Material.Shininess));
  vec3 specular = u_Light.Specular * spec *
                  vec3(texture(u_Material.Specular, TextureCoords)) *
                  u_Light.Color;

  vec3 Result = (ambient + diffuse + specular);

  FragColor = vec4(Result, 1.0);
}