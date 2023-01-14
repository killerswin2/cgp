
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

// build a return a scale matrix
mat4 buildScale(float x, float y, float z)
{
    mat4 translationMatrix = mat4(
            x, 0.0, 0.0, 0.0,
            0.0, y, 0.0, 0.0,
            0.0, 0.0, z, 0.0,
            0.0, 0.0, 0.0, 1);
    return translationMatrix;
}