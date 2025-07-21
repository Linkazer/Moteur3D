#version 330 core
#define MAX_MATERIAL_DIFFUSE 8
#define MAX_MATERIAL_SPECULAR 4
#define MAX_MATERIAL_NORMAL 1
#define MAX_MATERIAL_HEIGHT 1
#define MAX_LIGHT_POINT 4
#define MAX_LIGHT_DIRECTIONAL 2
#define MAX_LIGHT_SPOT 4

out vec4 FragColor;

struct Material {
    sampler2D diffuse[MAX_MATERIAL_DIFFUSE];
    sampler2D specular[MAX_MATERIAL_SPECULAR];
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;

    float linear;
    float quadratic;

    float cutoffAngle;
    float outerCutoffAngle;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
  
uniform Material material;
uniform Light pointLights[MAX_LIGHT_POINT];
uniform Light directionalLights[MAX_LIGHT_DIRECTIONAL];
uniform Light spotLights[MAX_LIGHT_SPOT];
uniform vec3 viewPos;

vec3 CalculateDirectionLight(Light light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 result;

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    for(int i = 0; i < MAX_LIGHT_DIRECTIONAL; i++)
    {
        result += CalculateDirectionLight(directionalLights[i], norm, viewDir);
    }

    for(int i = 0; i < MAX_LIGHT_POINT; i++)
    {
        result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
    }

     for(int i = 0; i < MAX_LIGHT_SPOT; i++)
    {
        result += CalculateSpotLight(spotLights[i], norm, FragPos, viewDir);
    }

    FragColor = vec4(result, 1.0);
} 

vec3 CalculateDirectionLight(Light light, vec3 normal, vec3 viewDir)
{
    //Ambient
    vec3 ambient = light.ambientColor * vec3(texture(material.diffuse[0], TexCoords));

    //Diffuse
    vec3 lightDir = normalize(light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuseColor * diff * vec3(texture(material.diffuse[0], TexCoords));

    //Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specularColor * spec * vec3(texture(material.specular[0], TexCoords));

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //Ambient
    vec3 ambient = light.ambientColor * vec3(texture(material.diffuse[0], TexCoords));

    //Diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuseColor * diff * vec3(texture(material.diffuse[0], TexCoords));

    //Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specularColor * spec * vec3(texture(material.specular[0], TexCoords));

    //Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //Ambient
    vec3 ambient = light.ambientColor * vec3(texture(material.diffuse[0], TexCoords));

    //Diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuseColor * diff * vec3(texture(material.diffuse[0], TexCoords));

    //Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specularColor * spec * vec3(texture(material.specular[0], TexCoords));

    //Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    //Spot edges
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutoffAngle - light.outerCutoffAngle;
    float intensity = clamp((theta - light.outerCutoffAngle) / epsilon, 0.0, 1.0);
    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    return (ambient + diffuse + specular);
}