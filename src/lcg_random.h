#ifndef LCG_RANDOM_H
#define LCG_RANDOM_H

void random_init();
void random_set_seed(int seed);
int random_get(int min, int max);

#endif