#version 330 core

in vec4 color;
in vec3 vLightWeight;
out vec4 fragColor;

void main() {
   fragColor = vec4(vLightWeight.rgb, 1.0);
   fragColor = color;
}
