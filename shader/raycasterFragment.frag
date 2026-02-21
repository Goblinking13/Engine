#version 330 core
out vec4 fragColor;

in vec3 fWorldPos;
flat in vec3 fCenter;
flat in vec3 fT;
flat in vec3 fB;

uniform float radius = 0.15;      // например 0.15 (в мировых единицах)
uniform float softness = 0.01;    // например 0.02 для мягкого края

void main() {
    vec3 d = fWorldPos - fCenter;

    // 2D координаты на плоскости треугольника (в world units)
    vec2 uv = vec2(dot(d, fT), dot(d, fB));

    float dist = length(uv);

    // маска круга с мягким краем
    float alpha = 1.0 - smoothstep(radius - softness, radius + softness, dist);

    if (alpha <= 0.001) discard;

    fragColor = vec4(1.0, 1.0, 0.0, alpha);
}