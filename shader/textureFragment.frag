#version 330 core

in vec3 oNormal;
in vec3 oColor;
in vec3 fragPos;
in vec2 TexCoord;

out vec4 fragColor;

vec3 lightPos= vec3(0,10,0);
vec3 lightColor = vec3(1,1,1);

float ambient = 0.5f;
float specularStrength = 1;

uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;


void main(){
vec4 basicColor = texture(texture_diffuse1, TexCoord);


vec3 norm = normalize(oNormal);
vec3 lightDir = normalize(lightPos - fragPos);

float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * lightColor;

vec3 viewDir = normalize(viewPos- fragPos);
vec3 reflectDir = reflect(-lightDir, norm);

float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = specularStrength * spec * lightColor;

vec3 result = (ambient + diffuse+specular) * vec3(basicColor);
fragColor = vec4(result, basicColor.w);

}
