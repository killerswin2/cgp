#version 430

layout (location=0) in vec3 position;

uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float timeFactor;

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

out vec4 varyingColor;

void main(void)
{
    float instanceTF = gl_InstanceID + timeFactor;
    float a = sin(203.0 * instanceTF / 8000.0) * 403.0;
    float b = sin(301.0 * instanceTF / 8000.0) * 401.0;
    float c = sin(400.0 * instanceTF / 8000.0) * 405.0;

    // build the rotation and translation matrices
    mat4 localRotX = buildRotateX(1000 * instanceTF);
    mat4 localRotY = buildRotateY(1000 * instanceTF);
    mat4 localRotZ = buildRotateZ(1000 * instanceTF);
    mat4 localTrans = buildTranslate(a, b, c);

    //build model view
    mat4 newM_matrix = localTrans * localRotX * localRotY * localRotZ;
    mat4 mv_matrix = v_matrix * newM_matrix;

    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}

// build a return a translation matrix
mat4 buildTranslate(float x, float y, float z)
{
    mat4 translationMatrix = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            x, y, z, 1);
    return translationMatrix;
}

// build and return a rotation matrix around the Z axis
mat4 buildRotateX(float rad)
{
    mat4 rotateMatrix = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(rad), -sin(rad), 0.0,
            0.0, sin(rad), cos(rad), 0.0,
            0.0, 0.0, 0.0, 1.0);
    return rotateMatrix;
}

// build and return a rotation matrix around the Y axis
mat4 buildRotateY(float rad)
{
    mat4 rotateMatrix = mat4(
            cos(rad), 0.0, sin(rad), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(rad), 0.0, cos(rad), 0.0,
            0.0, 0.0, 0.0, 1.0);
    return rotateMatrix;
}

// build and return a rotation matrix around the Z axis
mat4 buildRotateZ(float rad)
{
    mat4 rotateMatrix = mat4(
            cos(rad), -sin(rad), 0.0, 0.0,
            sin(rad), cos(rad), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0);
    return rotateMatrix;
}