#pragma once

double root (double (*)(double), double (*)(double),
             double (*)(double), double (*)(double),
             double, double, double);

double integral (double (*)(double), double, double, double);

void reset_counter (void);
unsigned get_counter (void);