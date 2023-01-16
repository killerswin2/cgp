#version 430

out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)      // we can access the coordinates of the fragment with gl_FragCoord
{
    color = vec4(1.0, 0.0, 0.0, 1.0);
}