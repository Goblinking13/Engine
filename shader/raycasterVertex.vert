#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float baseSize = 30.0f;
uniform float sizeScale = 1.0f;

out vec3 oColor;

void main() {
//model *
    vec4 viewPos = view * vec4(vPos, 1.0);

    gl_Position = projection * viewPos;

    float dist = max(0.001, -viewPos.z);

    gl_PointSize = baseSize * (sizeScale / dist);
    oColor = vColor;

}