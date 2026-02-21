//#version 330 core
//out vec4 fragColor;
//
//in vec3 fWorldPos;
//flat in vec3 fCenter;
//flat in vec3 fT;
//flat in vec3 fB;
//
//uniform float radius = 0.15;      // например 0.15 (в мировых единицах)
//uniform float softness = 0.01;    // например 0.02 для мягкого края
//
//void main() {
//    vec3 d = fWorldPos - fCenter;
//
//    // 2D координаты на плоскости треугольника (в world units)
//    vec2 uv = vec2(dot(d, fT), dot(d, fB));
//
//    float dist = length(uv);
//
//    // маска круга с мягким краем
//    float alpha = 1.0 - smoothstep(radius - softness, radius + softness, dist);
//
//    if (alpha <= 0.001) discard;
//
//    fragColor = vec4(1.0, 1.0, 0.0, alpha);
//}


#version 330 core
out vec4 fragColor;

in vec3 fWorldPos;
flat in vec3 fT;
flat in vec3 fB;

flat in float fHit;
flat in vec3  fHitPos;

uniform float radius = 0.08; // (в world units)
uniform float softness=  0.02;

void main() {
    // базовый цвет (можешь оставить свой)
    vec4 base = vec4(1.0, 1.0, 0.0, 0.0); // 0 alpha если хочешь только точку

    if (fHit < 0.5) {
        // нет пересечения — ничего не рисуем этим проходом
        discard;
    }

    vec3 d = fWorldPos - fHitPos;
    vec2 uv = vec2(dot(d, fT), dot(d, fB));
    float dist = length(uv);

    float a = 1.0 - smoothstep(radius - softness, radius + softness, dist);
    if (a <= 0.001) discard;

    fragColor = vec4(1.0, 0.2, 0.2, a); // красная точка
}