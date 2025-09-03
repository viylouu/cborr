#version 330 core

uniform sampler2D tex;
uniform vec2 samp_pos;
uniform vec2 samp_size;
uniform vec4 tint;

in vec2 uv;

out vec4 oCol;

void main() {
    vec4 samp = texture(tex, uv * samp_size + samp_pos) * tint;
    if (samp.a == 0) discard;
    oCol = samp;
}

