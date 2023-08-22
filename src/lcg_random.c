#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "lcg_random.h"

#define MINSTD 16807	//Park & Miller minimal standard = 7^5 = 16807, later revised as 48271
#define Q (INT_MAX / MINSTD)
#define R (INT_MAX % MINSTD)
#define ITERATION_COUNT 1000000

static int iy = 0;
static int iv[32];
static int idum;

static void seed_generator(int seed)
{
    int num = seed;
    if (num < 1)
    {
        num = 1;
    }

    for (int index = 39; index >= 0; index--)
    {
        num = MINSTD * (num % Q) - R * (num / Q);

        if (num < 0)
        {
            num &= INT_MAX;
        }

        if (index < 32)
        {
            iv[index] = num;
        }
    }

    iy = iv[0];
    idum = num;
}

static int ran1(int max)
{
    int v1 = MINSTD * (idum % Q) - R * (idum / Q);

    if (v1 < 0)
    {
        v1 += INT_MAX;	//adding max int
    }

    if (v1 < 0)
    {
        v1 += INT_MAX;	//if v1 originally MIN_INT, add MAX_INT again to ensure positive number
    }

    int v2 = iy & 0x1F;	//0x1F = 31
    int v3 = iv[v2];
    iv[v2] = v1;
    iy = v3;
    idum = v1;

    return v3 % max;
}

static unsigned int timer_read()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_sec;
}

static int random_seed()
{
    int high = rand() << 16;
    int low = rand();

    return (high + low) & INT_MAX;
}

void random_init()
{
    srand(timer_read());
    seed_generator(random_seed());
}

int random_get(int min, int max)
{
    int result;

    if (min <= max) {
        result = min + ran1(max - min + 1);
    } else {
        result = max + ran1(min - max + 1);
    }

    if (result < min || result > max) {
        printf("Random number %d is not in range %d to %d", result, min, max);
        result = min;
    }

    return result;
}