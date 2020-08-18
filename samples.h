#pragma once

extern const char * const str_func[];
extern double (* const func[])(double);
extern double (* const der_func[])(double);

void print_available (void);