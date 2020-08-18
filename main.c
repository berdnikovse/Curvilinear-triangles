#include "../headers/main.h"

int main (int argc, char **argv)
{
    if (argc < 2)
    {
        default_help ();
    }

    else if (!strcmp (argv[1], "-help"))
    {
        help ();
    }

    else if (!strcmp (argv[1], "-samples"))
    {
        print_available ();
    }

    else if (!strcmp (argv[1], "-combinations"))
    {
        print_combinations ();
    }

    else if (!strcmp (argv[1], "-test-root"))
    {
        root_test();
    }

    else if (!strcmp (argv[1], "-test-integral"))
    {
        int_test();
    }

    else if (!strcmp (argv[1], "-root"))
    {
        if (check_arguments (ARG_ROOT, argc - 2)) manual_root_test(argc, argv);
    }

    else if (!strcmp (argv[1], "-integral"))
    {
        if (check_arguments (ARG_INT, argc - 2)) manual_int_test(argc, argv);
    }

    else if (!strcmp (argv[1], "-area"))
    {
        if (check_arguments (ARG_AREA, argc - 2)) print_area (argc, argv);
    }

    else printf("unknown command; use -help to view manual\n\n");

    return 0;
}