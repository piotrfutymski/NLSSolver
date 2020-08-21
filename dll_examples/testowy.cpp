#include "testowy.h"
// X^2 + Y - 5
// X^2 + Y^2 -7
double f(const std::vector<double> & X, int n)
{
    if(n == 0)
        return  X[0]*X[0] + X[1] - 5;
    if(n == 1)
        return X[0]*X[0] + X[1]*X[1] - 7;
    return 0;
}

double df(const std::vector<double> & X, int n)
{
    if(n == 0)
        return 2 * X[0];
    if(n == 1)
        return 2 * X[1];
    return 0;
}

APIs api_table = {f, df};