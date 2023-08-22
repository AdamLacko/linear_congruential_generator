#include <stdio.h>

#include "lcg_random.h"

int main()
{
    random_init();
    int number = random_get(0, 100);

    printf("Random number: %d", number);
    
    return 0;
}