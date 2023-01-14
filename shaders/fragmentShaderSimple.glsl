#version 430

out vec4 color;
void main(void)      // we can access the coordinates of the fragment with gl_FragCoord
{
    if(gl_FragCoord.x < 300) {
        color = vec4(1.0, 0.0, 0.0, 1.0);
    } else 
    {
        color = vec4(0.0, 0.0, 1.0, 1.0);
    }
}