#include "../headers/comp.h"
#include "../headers/asmfunc.h"

#define diff(x) (f (x) - g (x))
#define der_diff(x) (der_f (x) - der_g (x))
#define INF 1e100

static unsigned curr_n_it;  //iteration counter

double integral (double (*f)(double), double a, double b, double eps)
{
    unsigned n_parts = 0x10;
    double prev_ans, ans = INF;
    do
    {
        ++curr_n_it;
        prev_ans = ans;
        ans = 0;
        for (unsigned i = 0; i < n_parts; i++)
        {
            ans += f ((a * (n_parts - i - 1) + b * (i + 1)) / n_parts);
            ans += f ((a * (n_parts - i) + b * i) / n_parts);
            ans += 4 * f ((a * (n_parts - i - 0.5) + b * (i + 0.5)) / n_parts);
        }
        ans *= (b - a) / (6 * n_parts);
        n_parts *= 2;
    } while (asm_fabs (ans - prev_ans) >= eps / 2);
    return ans;
}

double
root (double (*f)(double), double (*g)(double),
      double (*der_f)(double), double (*der_g)(double),
      double a, double b, double eps)
{
    while (asm_fabs(b - a) >= eps)
    {
        ++curr_n_it;
        if (f(a) > g(a))
        {
            double (*tmp)(double) = f;
            f = g;
            g = tmp;
            tmp = der_f;
            der_f = der_g;
            der_g = tmp;
        }

        double next_a, next_b;
        if (der_diff (b) - der_diff (a) > 0) //if (f - g) is convex
        {
            next_a = (a * diff (b) - b * diff (a)) / (diff(b) - diff (a));
            next_b = b - (diff (b)) / der_diff (b);
        }
        else //if (f - g) is concave
        {
            next_a = a - (diff (a)) / der_diff (a);
            next_b = (a * diff (b) - b * diff (a)) / (diff(b) - diff (a));
        }
        a = next_a;
        b = next_b;
    }
    return (a + b) / 2;
}

void reset_counter (void)
{
    curr_n_it = 0;
}

unsigned get_counter (void)
{
    return curr_n_it;
}