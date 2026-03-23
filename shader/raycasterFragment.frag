#version 330 core
out vec4 FragColor;

//uniform vec3 color = vec3(0.0, 1.0, 0.0);
in vec3 oColor;

void main()
{
    vec2 coord = gl_PointCoord * 2.0 - 1.0;
    float r2 = dot(coord, coord);

    if (r2 > 1.0)
        discard;

    FragColor = vec4(oColor, 1.0f - r2/2.0f);
}