#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 vWorldPos[];

out vec3 fWorldPos;       // будет интерполироваться
flat out vec3 fCenter;    // одинаковый для всего треугольника
flat out vec3 fT;         // tangent в плоскости треугольника
flat out vec3 fB;         // bitangent

void main() {
    vec3 p0 = vWorldPos[0];
    vec3 p1 = vWorldPos[1];
    vec3 p2 = vWorldPos[2];

    // центр треугольника
    fCenter = (p0 + p1 + p2) / 3.0;

    // нормаль
    vec3 n = normalize(cross(p1 - p0, p2 - p0));

    // базис в плоскости
    fT = normalize(p1 - p0);
    fB = normalize(cross(n, fT));

    // выпустить тот же треугольник
    for (int i = 0; i < 3; i++) {
        fWorldPos = vWorldPos[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}