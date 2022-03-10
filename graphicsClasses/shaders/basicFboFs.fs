#version 300 es
precision highp float;


uniform sampler2D frameTexture;
uniform float averageLuminance;

in vec2 fs_vertexUVs;
out vec4 pixelColor;


void main() {
    pixelColor = texture(frameTexture, fs_vertexUVs);
    // pixelColor = vec4(1.0,1.0,1.0,1.0);
}
