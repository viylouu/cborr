#ifndef VEC_H
#define VEC_H

typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    float x;
    float y;
    float z;
} vec3;

static inline vec2 cbVec2Add(vec2 a, vec2 b)  { return (vec2){ a.x+b.x, a.y+b.y }; }
static inline vec3 cbVec3Add(vec3 a, vec3 b)  { return (vec3){ a.x+b.x, a.y+b.y, a.z+b.z}; }
static inline vec2 cbVec2Mult(vec2 a, vec2 b) { return (vec2){ a.x*b.x, a.y*b.y }; }
static inline vec3 cbVec3Mult(vec3 a, vec3 b) { return (vec3){ a.x*b.x, a.y*b.y, a.z*b.z}; }

#endif
