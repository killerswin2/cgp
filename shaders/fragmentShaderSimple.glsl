#version 430

in vec2 tc;

out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

layout(binding=0) uniform sampler2D samp;

void main(void)      // we can access the coordinates of the fragment with gl_FragCoord
{
    color = texture(samp, tc);
}