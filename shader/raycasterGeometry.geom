//#version 330 core
//layout(triangles) in;
//layout(triangle_strip, max_vertices = 3) out;
//
//uniform vec3 viewPos;
//uniform vec3 viewDir;
//
//in vec3 vWorldPos[];
//
//out vec3 fWorldPos;
//flat out vec3 fCenter;
//flat out vec3 fT;
//flat out vec3 fB;
//
//void main() {
//    vec3 p0 = vWorldPos[0];
//    vec3 p1 = vWorldPos[1];
//    vec3 p2 = vWorldPos[2];
//
//    // центр треугольника
//    fCenter = (p0 + p1 + p2) / 3.0;
//
//    // нормаль
//    vec3 n = normalize(cross(p1 - p0, p2 - p0));
//
//    // базис в плоскости
//    fT = normalize(p1 - p0);
//    fB = normalize(cross(n, fT));
//
//    // выпустить тот же треугольник
//    for (int i = 0; i < 3; i++) {
//        fWorldPos = vWorldPos[i];
//        gl_Position = gl_in[i].gl_Position;
//        EmitVertex();
//    }
//    EndPrimitive();
//}

#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform vec3 viewPos;   // origin луча (камера)
uniform vec3 viewDir;   // direction луча (камера), лучше нормализованный

in vec3 vWorldPos[];

out vec3 fWorldPos;
flat out vec3 fCenter;
flat out vec3 fT;
flat out vec3 fB;

// NEW:
flat out float fHit;      // 1.0 если пересечение есть, иначе 0.0
flat out vec3  fHitPos;   // точка пересечения в world space

bool mollerTrumbore(vec3 orig, vec3 dir, vec3 v0, vec3 v1, vec3 v2,
                    out float t, out float u, out float v)
{
    const float EPS = 1e-6;

    vec3 e1 = v1 - v0;
    vec3 e2 = v2 - v0;

    vec3 p = cross(dir, e2);
    float det = dot(e1, p);

    // если хочешь учитывать обе стороны треугольника:
    if (abs(det) < EPS) return false;
    float invDet = 1.0 / det;

    vec3 T = orig - v0;
    u = dot(T, p) * invDet;
    if (u < 0.0 || u > 1.0) return false;

    vec3 q = cross(T, e1);
    v = dot(dir, q) * invDet;
    if (v < 0.0 || u + v > 1.0) return false;

    t = dot(e2, q) * invDet;
    if (t <= EPS) return false; // пересечение “позади” или слишком близко

    return true;
}

void main() {
    vec3 p0 = vWorldPos[0];
    vec3 p1 = vWorldPos[1];
    vec3 p2 = vWorldPos[2];

    // центр треугольника
    fCenter = (p0 + p1 + p2) / 3.0;

    // нормаль и базис плоскости (для рисования кружка в FS)
    vec3 n = normalize(cross(p1 - p0, p2 - p0));
    fT = normalize(p1 - p0);
    fB = normalize(cross(n, fT));

    // ---- Möller–Trumbore ----
    float t, u, v;
    vec3 dir = normalize(viewDir);
    bool hit = mollerTrumbore(viewPos, dir, p0, p1, p2, t, u, v);

    fHit = hit ? 1.0 : 0.0;
    fHitPos = hit ? (viewPos + dir * t) : vec3(0.0);

    // выпустить тот же треугольник
    for (int i = 0; i < 3; i++) {
        fWorldPos = vWorldPos[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}