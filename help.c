#include <stdio.h>
#include "../headers/help.h"
#include "../headers/asmfunc.h"
#include "../headers/constants.h"

void default_help (void)
{
    printf ("supported options:\n");
    printf ("-help\n");
    printf ("-samples\n");
    printf ("-combinations\n");
    printf ("-test-root\n");
    printf ("-test-integral\n");
    printf ("-root n_func_1 n_func_2 left right [precision]\n");
    printf ("-integral n_func left right [precision]\n");
    printf ("-area n_option -mode [precision]\n");
    printf ("\n");
}

void help (void)
{
    char format[50] = { 0 };
    unsigned prec = count_prec (DEFAULT_EPS);
    sprintf (format, "%s%u%s", "%s %.", prec, "lf");
    char accuracy_msg[200] = { 0 };
    sprintf (accuracy_msg, format,
    "\'precision\' (optional) stands for desired accuracy; default accuracy is", DEFAULT_EPS);

    printf ("-samples\n");
    printf ("\t%s\n\n", "prints list of all functions, which can be used to test \'root\' and \'integral\'");

    printf ("-combinations\n");
    printf ("\t%s\n\n", "prints list of all function combinations, which can be used with \'area\'");

    printf ("-test-root\n");
    printf ("\t%s\n\n", "performs testing of \'root\' on a basic set of tests and prints complete report");

    printf ("-test-integral\n");
    printf ("\t%s\n\n", "performs testing of \'integral\' on a basic set of tests and prints complete report");

    printf ("-root n_func_1 n_func_2 left right [precision]\n");
    printf ("\t%s\n", "finds such x in interval (\'left\', \'right\') that f(x) = g(x)");
    printf ("\t%s\n", "\'n_func_1\' and \'n_func_2\' stand for numbers of functions f(x) and g(x) respectively");
    printf ("\t%s\n\n", accuracy_msg);

    printf ("-integral n_func left right [precision]\n");
    printf ("\t%s\n", "computes an integral of f(x) in inverval (\'left\', \'right\')");
    printf ("\t%s\n", "\'n_func\' stands for number of function f(x)");
    printf ("\t%s\n\n", accuracy_msg);

    printf ("-area n_option -mode [precision]\n");
    printf ("\t%s\n", "computes an area of curvilinear triangle formed by graphs of three functions");
    printf ("\t%s\n", "\'n_option\' stands for number of function combination");
    printf ("\t%s\n", "\'-mode\' can be either \'-points\', \'-iterations\', \'-answer\' or \'-all\'");
    printf ("\t\t%s\n", "-points prints coordinates of curvilinear triangle verteces");
    printf ("\t\t%s\n", "-iterations prints number of iterations needed to compute area");
    printf ("\t\t%s\n", "-answer prints computed area");
    printf ("\t\t%s\n", "-all prints all the information");
    printf ("\t%s\n\n", accuracy_msg);
}

bool check_arguments (unsigned normal, int argc)
{
    if (argc < normal)
    {
        printf ("invalid number of arguments; use -help to view manual\n\n");
        return false;
    }
    return true;
}