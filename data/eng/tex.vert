#version 430 core

struct InstanceData {
    mat4 trans;
    vec2 pos;
    vec2 size;
    vec2 sampPos;
    vec2 sampSize;
    vec4 col;
};

layout(std430, binding = 0) buffer batchSSBO {
    InstanceData insts[];
};

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
    InstanceData data = insts[gl_VertexID / 6];

    gl_Position = proj * data.trans * vec4(vert * data.size + data.pos, 0,1);
    
    sampPos = data.sampPos;
    sampSize = data.sampSize;
    col = data.col;
    uv = vert;
}
