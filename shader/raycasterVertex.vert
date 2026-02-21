#version 330 core
layout (location = 0) in vec3 vPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float baseSize = 60.0f;
uniform float sizeScale = 1.0f;

void main() {
    vec4 viewPos = view * model * vec4(vPos, 1.0);

    gl_Position = projection * viewPos;

    float dist = max(0.001, -viewPos.z);

    gl_PointSize = baseSize * (sizeScale / dist);
}