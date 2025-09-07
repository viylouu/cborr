#version 430 core

const vec2 verts[6] = vec2[6](
    vec2(0,0), vec2(1,0), vec2(1,1),
    vec2(1,1), vec2(0,1), vec2(0,0)
        );

struct InstanceData {
    mat4 trans;
    vec2 pos;
    vec2 size;
    vec4 _unused;
    vec4 col;
};

layout(std430, binding = 0) buffer batchSSBO {
    InstanceData insts[];
};

//uniform vec3 pos;
//uniform vec2 size;

uniform mat4 proj;
//uniform mat4 trans;

flat out vec4 col;

void main() {
    vec2 vert = verts[gl_VertexID % 6];
    InstanceData data = insts[gl_VertexID / 6];

    gl_Position = proj * data.trans * vec4(vert * data.size + data.pos, 0,1);
    col = data.col;
}
