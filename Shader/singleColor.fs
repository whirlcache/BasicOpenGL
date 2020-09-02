#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D outTexture;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec4 result = vec4(ambient + diffuse, 1.0);
	FragColor = result;
}