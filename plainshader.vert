#version 330 core

layout(location = 0) in vec4 positionAttr;
layout(location = 1) in vec4 colorAttr;
out vec4 color;
uniform mat4 pmatrix;
uniform mat4 vmatrix;
uniform mat4 matrix;

// Beregner vha Phong shading
out vec3 vLightWeight;

void main() {
    vec4 vertexPositionEye4 = matrix * positionAttr;
    vec3 vertexPositionEye3 = vertexPositionEye4.xyz;
    vec4 temp = vmatrix*matrix *colorAttr;
    vec3 normalEye = normalize(temp.xyz);
    vec3 viewVectorEye = - normalize(vertexPositionEye3);
    gl_Position = pmatrix*vmatrix*matrix * positionAttr;
    color = colorAttr;//*vec4(1.0, 0.5, 0.2, 1.0);//
}
