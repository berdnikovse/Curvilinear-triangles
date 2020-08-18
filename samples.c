#include <stdio.h>
#include "../headers/samples.h"
#include "../headers/sampfunc.h"

const char * const str_func[] = {
    "2^x + 1",
    "x^5",
    "(1 - x) / 3",
    "3 * (0.5 / (x + 1) + 1)",
    "2.5 * x - 9.5",
    "5 / x",
    "e^(-x) + 3",
    "2 * x - 2",
    "1 / x",
    "e^x + 2",
    "-1 / x",
    "-2 * (x + 1) / 3",
};

double (* const func[])(double) = {
    f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12
};

double (* const der_func[])(double) = {
    g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12
};

enum {
    n_samples = sizeof (func) / sizeof (func[0])
};

void print_available (void)
{
    printf ("available functions:\n");
    for (unsigned i = 0; i < n_samples; i++)
    {
        printf ("%2u: %s\n", i + 1, str_func[i]);
    }
    printf ("\n");
}