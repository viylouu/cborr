#version 330 core

uniform sampler2D tex;

flat in vec2 sampPos;
flat in vec2 sampSize;
flat in vec4 col;
in vec2 uv;

out vec4 oCol;

void main() {
    vec4 samp = texture(tex, uv * sampSize + sampPos) * col;
    if (samp.a == 0) discard;
    oCol = samp;
}

