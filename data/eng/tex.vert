#version 330 core

struct InstanceData {
    mat4 trans;
    vec2 pos;
    vec2 size;
};

uniform samplerBuffer insts;

const vec2 verts[6] = vec2[6](
    vec2(0,0), vec2(1,0), vec2(1,1),
    vec2(1,1), vec2(0,1), vec2(0,0)
        );

uniform mat4 proj;

flat out vec2 sampPos;
flat out vec2 sampSize;
flat out vec4 col;

out vec2 uv;

void main() {
    vec2 vert = verts[gl_VertexID % 6];
    InstanceData data;
    int base = gl_InstanceID * 7;
    data.trans = mat4(
        texelFetch(insts, base + 0),
        texelFetch(insts, base + 1),
        texelFetch(insts, base + 2),
        texelFetch(insts, base + 3)
        );
    data.pos = texelFetch(insts, base + 4).xy;
    data.size = texelFetch(insts, base + 4).zw;

    gl_Position = proj * data.trans * vec4(vert * data.size + data.pos, 0,1);

    sampPos = texelFetch(insts, base + 5).xy;
    sampSize = texelFetch(insts, base + 5).zw;
    col = texelFetch(insts, base +6).rgba;
    uv = vert;
}
