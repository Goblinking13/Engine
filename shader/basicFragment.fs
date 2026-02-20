#version 330 core

uniform vec3 viewPos;

in vec3 oNormal;
in vec3 oColor;
in vec3 fragPos;
out vec4 fragColor;


vec3 lightPos= vec3(0,5,0);
vec3 lightColor = vec3(1,1,1);

float ambient = 0.5f;
float specularStrength = 0.5f;

void main(){

//vec3 norm = normalize(oNormal);
//vec3 lightDir = normalize(vec3(0,1,0));
//vec3 lightDir = normalize(lightPos - fragPos);

//float diff = max(dot(norm, lightDir), 0.0);
//vec3 diffuse = diff * lightColor;

//vec3 viewDir = normalize(viewPos- fragPos);
//vec3 reflectDir = reflect(-lightDir, norm);

// float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
// vec3 specular = specularStrength * spec * lightColor;



// vec3 result = (ambient + diffuse+specular) * oColor;
// vec3 result = (ambient + diffuse+specular) * oColor;
fragColor = vec4(oColor, 1.0);
//  fragColor = vertexColor;

}
