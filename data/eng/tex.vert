#version 330 core

const vec2 verts[6] = vec2[6](
    vec2(0,0), vec2(1,0), vec2(1,1),
    vec2(1,1), vec2(0,1), vec2(0,0)
        );

uniform vec2 pos;
uniform vec2 size;

uniform mat4 proj;

out vec2 uv;

void main() {
    gl_Position = proj * vec4(verts[gl_VertexID] * size + pos, 0,1);
    uv = vec2(0,1) - verts[gl_VertexID];
}
