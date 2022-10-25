#version 330 core

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct DirectionalLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight {
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct SpotLight {
  vec3 position;
  vec3 direction;

  float innerCutOff;
  float outerCutOff;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec3 Normal;
in vec2 TextureCoords;
in vec3 FragPosition;

uniform vec3 u_CameraPosition;
uniform Material u_Material;

uniform DirectionalLight u_DirectionalLight;
#define NUM_POINT_LIGHTS 4
uniform PointLight u_PointLights[NUM_POINT_LIGHTS];
uniform SpotLight u_SpotLight;

out vec4 FragColor;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);

void main() {
  vec3 norm = normalize(Normal);
  vec3 viewDirection = normalize(u_CameraPosition - FragPosition);

  // Directional Lights
  vec3 result = CalculateDirectionalLight(u_DirectionalLight, norm, viewDirection);

  // Point Lights
  for (int i = 0; i < NUM_POINT_LIGHTS; i++) {
    result += CalculatePointLight(u_PointLights[i], norm, FragPosition, viewDirection);
  }

  // Spot Lights
  result += CalculateSpotLight(u_SpotLight, norm, FragPosition, viewDirection);

  FragColor = vec4(result, 1.0);  
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
  vec3 lightDirection = normalize(-light.direction);
  // Diffuse
  float diff = max(dot(normal, lightDirection), 0.0);

  // Specular
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess);

  // Results
  vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, TextureCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, TextureCoords));
  vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, TextureCoords));
  
  return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection) {
  vec3 lightDirection = normalize(light.position - fragPosition);
  // Diffuse
  float diff = max(dot(normal, lightDirection), 0.0);

  // Specular
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess);

  // Attenuation
  float distance = length(light.position - fragPosition);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  // Results
  vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, TextureCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, TextureCoords));
  vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, TextureCoords));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  
  return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection) {
  vec3 lightDirection = normalize(light.position - fragPosition);
  // Diffuse
  float diff = max(dot(normal, lightDirection), 0.0);

  // Specular
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess);

  // Soft edges
  float theta = dot(lightDirection, normalize(-light.direction));
  float epsilon = light.innerCutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

  // Results
  vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, TextureCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, TextureCoords));
  vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, TextureCoords));

  diffuse *= intensity;
  specular *= intensity;

  return (ambient + diffuse + specular);
}


