#version 330 core

const vec2 verts[6] = vec2[6](
    vec2(0,0), vec2(1,0), vec2(1,1),
    vec2(1,1), vec2(0,1), vec2(0,0)
        );

uniform vec3 pos;
uniform vec2 size;

uniform mat4 proj;
uniform mat4 trans;

void main() {
    gl_Position = proj * trans * vec4(vec3(verts[gl_VertexID] * size, 0) + pos,1);
}
