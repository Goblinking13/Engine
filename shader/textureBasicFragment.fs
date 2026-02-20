#version 330 core

in vec4 vertexColor;
out vec4 fragColor;
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
// uniform sampler2D texture_specular1;
// uniform sampler2D texture_normal1;
// uniform sampler2D texture_height1;

void main(){
 fragColor = texture(texture_diffuse1, TexCoord);
//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
// fragColor = vertexColor;

// if(texColor.a < 0.5)
//         discard;

//  fragColor = texColor;
}
