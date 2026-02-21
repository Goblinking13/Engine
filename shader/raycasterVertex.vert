#version 330 core
layout (location = 0) in vec3 vPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float baseSize = 15.0f;   // например 15.0
uniform float sizeScale = 60.0f;  // например 60.0 (подбирается)

void main() {
    vec4 viewPos = view * model * vec4(vPos, 1.0);

    gl_Position = projection * viewPos;

    // z в view space обычно отрицательный перед камерой, берём расстояние по оси камеры
    float dist = max(0.001, -viewPos.z);

    gl_PointSize = baseSize * (sizeScale / dist);
}