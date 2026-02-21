#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 inverseModel;

//out vec4 vertexColor;
out vec2 TexCoord;

out vec3 oNormal;
out vec3 fragPos;


void main(){

gl_Position = projection  *view*model * vec4(vPos,1.0f);

//vertexColor = vec4(vColor,1.0f);

fragPos = vec3(model*vec4(vPos,1.0f));
oNormal = mat3(transpose(inverseModel)) * vNormal;
//oNormal = mat3(transpose(inverseModel)) * vNormal;

TexCoord =  aTexCoord;
//gl_Position = view * vec4(vPos,1.0f);
}