#include <stdio.h>
#include "eng/phys/phys.h"

int main() {
    //do %f when printing floats
    printf("%f\n", cbCheckDistance2d(0,0, 10, 0));
    printf("%f\n", GRAV);
    printf("%.5f\n", PI);
    printf("%f\n", cbCheckDistance3d(7,4,3,17,6,2));
    return 0;
}