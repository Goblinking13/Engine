#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 inverseModel;

uniform vec3 vColor;

out vec3 oNormal;
out vec3 fragPos;
out vec3 oColor;


void main(){

gl_Position = projection  *view*model * vec4(vPos,1.0f);

fragPos = vec3(model*vec4(vPos,1.0f));
oNormal = mat3(transpose(inverseModel)) * vNormal;
//oNormal = vNormal;
oColor = vColor;

//gl_Position = view * vec4(vPos,1.0f);
}
