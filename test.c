#include "eng/phys/phys.h"
#include "eng/vec/vec.h"
#include <stdio.h>

vec2 pos1 = {3,5};
vec2 pos2 = {5,9};

int main(){
    printf("%f", cbCheckDistance2d(pos1, pos2));
}
