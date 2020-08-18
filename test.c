#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../headers/test.h"
#include "../headers/comp.h"
#include "../headers/samples.h"
#include "../headers/asmfunc.h"
#include "../headers/basic_testfunc.h"
#include "../headers/constants.h"

typedef struct test
{
    double (*func[4])(double);
    unsigned number[2];
    double left;
    double right;
    double eps;
    double answer;
} test;

enum {
    NON = -1
};

static const char * const str_test_set[] = {
    "x^2",
    "2 * x + 3",
    "x",
    "cos(x)",
    "e^x",
    "1 / x",
    "sqrt(1 - x^2)"
};

static const test root_test_set[] = {
    {{test1, test2, der_test1, der_test2}, {0, 1}, 1, 5, 0.1, 3},
    {{test1, test2, der_test1, der_test2}, {0, 1}, 0.5, 10, 0.0001, 3},
    {{test1, test2, der_test1, der_test2}, {0, 1}, 0.1, 20, 0.0000001, 3},
    {{test3, test4, der_test3, der_test4}, {2, 3}, 0, 1.5, 0.1, 0.7390851332151606416553120876738734040134},
    {{test3, test4, der_test3, der_test4}, {2, 3}, 0.2, 1.3, 0.0001, 0.7390851332151606416553120876738734040134},
    {{test3, test4, der_test3, der_test4}, {2, 3}, 0.4, 1.1, 0.0000001, 0.7390851332151606416553120876738734040134},
    {{test5, test6, der_test5, der_test6}, {4, 5}, 0.2, 10, 0.0001, 0.5671432904097838729999686622103555497538},
    {{test5, test6, der_test5, der_test6}, {4, 5}, 0.1, 15, 0.0000001, 0.5671432904097838729999686622103555497538},
    {{test5, test6, der_test5, der_test6}, {4, 5}, 0.2, 17, 0.0001, 0.5671432904097838729999686622103555497538},
};

static const test int_test_set[] = {
    {{test1, NULL, NULL, NULL}, {0, NON}, 0, 5, 0.1, 41.6666666666666666666666666666666666},
    {{test4, NULL, NULL, NULL}, {3, NON}, 0, 1, 0.01, 0.841470984807896506652502321630298999},
    {{test6, NULL, NULL, NULL}, {5, NON}, 1, 2, 0.00000001, 0.693147180559945309417},
    {{test7, NULL, NULL, NULL}, {6, NON}, -1, 1, 0.000000001, 1.570796326794896619231},
};

enum test_sizes{
    root_test_size = sizeof (root_test_set) / sizeof (root_test_set[0]),
    int_test_size = sizeof (int_test_set) / sizeof (int_test_set[0])
};

void root_test (void)
{
    unsigned passed = 0;
    double answer;
    char format[100] = { 0 };
    bool is_correct;
    reset_counter ();
    for (unsigned i = 0; i < root_test_size; i++)
    {
        printf ("searching root for f(x) = [%s] and g(x) = [%s]\n",
        str_test_set[root_test_set[i].number[0]], str_test_set[root_test_set[i].number[1]]);

        unsigned prec = count_prec (root_test_set[i].eps);
        sprintf (format, "%s%u%s%u%s%u%s", "left = %.", prec,
        "lf, right = %.", prec, "lf, eps = %.", prec, "lf\n");

        printf (format, root_test_set[i].left, root_test_set[i].right, root_test_set[i].eps);

        answer = root (root_test_set[i].func[0], root_test_set[i].func[1],
                       root_test_set[i].func[2], root_test_set[i].func[3], 
                       root_test_set[i].left, root_test_set[i].right, root_test_set[i].eps);
            
        sprintf (format, "%s%u%s%u%s", "%u iterations: %.", prec,
        "lf, correct answer is %.", prec, "lf\n");
        printf (format, get_counter (), answer, root_test_set[i].answer);

        is_correct = asm_fabs (answer - root_test_set[i].answer) < root_test_set[i].eps;
        passed += is_correct;
        printf (is_correct ? "OK\n\n" : "WRONG\n\n");
        reset_counter ();
    }
    printf ("passed %u tests out of %u\n", passed, root_test_size);
}

void int_test (void)
{
    unsigned passed = 0;
    double answer;
    char format[100] = { 0 };
    bool is_correct;
    reset_counter ();
    for (unsigned i = 0; i < int_test_size; i++)
    {
        printf ("integrating f(x) = [%s] in ",
        str_test_set[int_test_set[i].number[0]]);

        unsigned prec = count_prec (int_test_set[i].eps);
        sprintf (format, "%s%u%s%u%s%u%s", "[%.", prec, "lf, %.", prec, "lf], eps = %.", prec, "lf\n");
        printf (format, int_test_set[i].left, int_test_set[i].right, int_test_set[i].eps);

        answer = integral (int_test_set[i].func[0], int_test_set[i].left, int_test_set[i].right, int_test_set[i].eps);

        sprintf (format, "%s%u%s%u%s", "%u iterations: %.", prec,
        "lf, correct answer is %.", prec, "lf\n");
        printf (format, get_counter (), answer, int_test_set[i].answer);

        is_correct = asm_fabs (answer - int_test_set[i].answer) < int_test_set[i].eps;
        passed += is_correct;
        printf (is_correct ? "OK\n\n" : "WRONG\n\n");
        reset_counter ();
    }
    printf ("passed %u tests out of %u\n", passed, int_test_size);
}

void manual_root_test (int argc, char **argv)
{
    unsigned n_func[2];
    double left, right, answer, eps = DEFAULT_EPS;
    char format[100] = { 0 };
    reset_counter ();

    sscanf (argv[2], "%u", &n_func[0]);
    sscanf (argv[3], "%u", &n_func[1]);
    sscanf (argv[4], "%lf", &left);
    sscanf (argv[5], "%lf", &right);
    if (argc >= 7) sscanf (argv[6], "%lf", &eps);

    answer = root (func[n_func[0] - 1], func[n_func[1] - 1],
    der_func[n_func[0] - 1], der_func[n_func[1] - 1], left, right, eps);
    sprintf (format, "%s%u%s", "%u interations: %.", count_prec (eps), "lf\n");
    printf (format, get_counter (), answer);
}

void manual_int_test (int argc, char **argv)
{
    unsigned n_func[2];
    double left, right, answer, eps = DEFAULT_EPS;
    char format[100] = { 0 };
    reset_counter ();

    sscanf (argv[2], "%u", &n_func[0]);
    sscanf (argv[3], "%lf", &left);
    sscanf (argv[4], "%lf", &right);
    if (argc >= 6) sscanf (argv[5], "%lf", &eps);

    answer = integral (func[n_func[0] - 1], left, right, eps);
    sprintf (format, "%s%u%s", "%u interations: %.", count_prec (eps), "lf\n");
    printf (format, get_counter (), answer);
}