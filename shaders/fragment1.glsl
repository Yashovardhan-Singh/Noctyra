#version 330 core

out vec4 FragCol;

in vec2 texCoord;

uniform sampler2D uTex;

void main() {
    FragCol = texture(uTex, texCoord);
}