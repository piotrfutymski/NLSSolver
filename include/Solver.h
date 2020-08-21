#pragma once
#include <vector>   

struct APIs{
double (*f_x)(const std::vector<double> & X, int n);
double (*df_x)(const std::vector<double> & X, int n);
};


inline int solveEquations(std::vector<double> & result, void * f_table, const std::vector<double> & start_solution, 
                    int max_iter = 100, double err = 1E-10, double omega = 1.0)
{
    APIs * eq_system = (APIs * )(f_table);

    int itNum = 0;
    auto sol = start_solution;
    while(itNum < max_iter)
    {
        auto mval = sol;
        bool tobreak = true;
        for (int i = 0; i < sol.size(); i++)
        {
            sol[i] = mval[i] - omega * eq_system->f_x(sol,i) / eq_system->df_x(sol,i); 
            if(sol[i] - mval[i] > err*omega || sol[i]-mval[i] < -1 * err * omega)
                tobreak = false;
        }

        if(tobreak)
            break;

        ++itNum;
    }

    result = sol;

    if(itNum < max_iter)
        return 0;

    if(itNum >= max_iter)
        return 1;
}