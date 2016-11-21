#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

out vec4 color;

uniform Material material;
uniform Light light;

void main()
{
	vec3 diffMap = vec3(texture(material.diffuse, TexCoords));
	vec3 specMap = vec3(texture(material.specular, TexCoords));

	vec3 ambient = light.ambient * diffMap;

	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light.position - Position);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse =  light.diffuse * (diffMap * diff);

	vec3 reflectDirection = reflect(-lightDirection, norm);
	vec3 viewDirection = normalize(-Position);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specular * (specMap * spec);

	vec3 result = specular + diffuse + ambient;
	color = vec4(result, 1.0f);
}