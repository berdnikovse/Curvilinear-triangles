#include <stdio.h>
#include <string.h>
#include "../headers/area.h"
#include "../headers/comp.h"
#include "../headers/samples.h"
#include "../headers/asmfunc.h"
#include "../headers/constants.h"

typedef struct area_test
{
    unsigned option;
    double intervals[3][2];
} area_test;

const area_test area_test_set[] = {
    {0, {{0, 3}, {-5, 5}, {1, 5}}},
    {1, {{0.5, 10}, {0.5, 10}, {0.5, 10}}},
    {2, {{0.1, 10}, {0.1, 10}, {0.1, 10}}},
    {3, {{-10, -0.1}, {-10, -0.1}, {-10, -0.1}}}
};

enum {
    n_options = sizeof (area_test_set) / sizeof (area_test_set[0])
};

typedef enum mode_type {
    ERRMODE,
    POINTS,
    ITERATIONS,
    ANSWER,
    ALL
} mode_type;

mode_type det_mode (char *mode_str)
{
    if (!strcmp (mode_str, "-points")) return POINTS;
    if (!strcmp (mode_str, "-iterations")) return ITERATIONS;
    if (!strcmp (mode_str, "-answer")) return ANSWER;
    if (!strcmp (mode_str, "-all")) return ALL;
    return ERRMODE;
}

double count_area (area_test curr_test, double points[], double eps)
{
    points[0] = root (func[3 * curr_test.option + 1], func[3 * curr_test.option + 2],
                      der_func[3 * curr_test.option + 1], der_func[3 * curr_test.option + 2],
                      curr_test.intervals[1][0], curr_test.intervals[1][1], eps * ROOT_SC_FACTOR);

    points[1] = root (func[3 * curr_test.option + 2], func[3 * curr_test.option + 0],
                      der_func[3 * curr_test.option + 2], der_func[3 * curr_test.option + 0],
                      curr_test.intervals[2][0], curr_test.intervals[2][1], eps * ROOT_SC_FACTOR);

    points[2] = root (func[3 * curr_test.option + 0], func[3 * curr_test.option + 1],
                      der_func[3 * curr_test.option + 0], der_func[3 * curr_test.option + 1],
                      curr_test.intervals[0][0], curr_test.intervals[0][1], eps * ROOT_SC_FACTOR);
    
    double answer = integral (func[3 * curr_test.option + 0], points[1], points[2], eps * INT_SC_FACTOR)
                  + integral (func[3 * curr_test.option + 1], points[2], points[0], eps * INT_SC_FACTOR)
                  + integral (func[3 * curr_test.option + 2], points[0], points[1], eps * INT_SC_FACTOR);

    return asm_fabs (answer);
}

void print_area (int argc, char **argv)
{
    unsigned option;
    double points[3], eps = DEFAULT_EPS;

    sscanf (argv[2], "%u", &option), option--;
    if (argc >= 5) sscanf (argv[4], "%lf", &eps);
    reset_counter ();

    char format[100] = { 0 };
    mode_type mode = det_mode (argv[3]);

    if (mode == ERRMODE)
    {
        printf ("function area:\n");
        printf ("\tunknown mode; use -help to view list of possible modificators\n\n");
        return;
    }

    unsigned prec = count_prec (eps);
    double answer = count_area (area_test_set[option], points, eps);

    printf ("current functions:\n");
    printf ("\tf(x) = [%s]\n", str_func[3 * option + 0]);
    printf ("\tg(x) = [%s]\n", str_func[3 * option + 1]);
    printf ("\th(x) = [%s]\n\n", str_func[3 * option + 2]);

    if (mode == ALL || mode == ITERATIONS)
    {
        printf ("computation complete; %u iterations used\n\n", get_counter ());
    }

    if (mode == ALL || mode == POINTS)
    {
        sprintf (format, "%s%u%s%u%s", "%s(%.", prec, "lf, %.", prec, "lf);\n");
        printf (format, "g(x) and h(x) intersect each other at point A", points[0], func[3 * option + 1](points[0]));
        printf (format, "h(x) and f(x) intersect each other at point B", points[1], func[3 * option + 2](points[1]));
        printf (format, "f(x) and g(x) intersect each other at point C", points[2], func[3 * option + 0](points[2]));
        printf ("\n");
    }

    if (mode == ALL || mode == ANSWER)
    {
        sprintf (format, "%s%u%s", "%s %.", prec, "lf\n\n");
        printf (format, "area of curvilinear triangle ABC is equal to", answer);
    }
}

void print_combinations (void)
{
    for (unsigned i = 0; i < n_options; i++)
    {
        printf ("combination %u:\n", i + 1);
        printf ("\tf(x) = [%s]\n\tg(x) = [%s]\n\th(x) = [%s]\n\n",
        str_func[i * 3 + 0], str_func[i * 3 + 1], str_func[i * 3 + 2]);
    }
}