#pragma once
#include <vector>   
#include <cmath>
#include "Interval.h"

inline int solveEquations(std::vector<double> & result, double (*f_x) (const std::vector<double> &, int), 
double (*df_x) (const std::vector<double> &, int) , const std::vector<double> & start_solution, 
                    int max_iter = 100, double err = 1E-10, double omega = 1.0)
{

    int itNum = 0;
    auto sol = start_solution;
    while(itNum < max_iter)
    {
        auto mval = sol;
        bool tobreak = true;
        for (int i = 0; i < sol.size(); i++)
        {
            sol[i] = mval[i] - omega * f_x(sol,i) / df_x(sol,i); 
            if(sol[i] - mval[i] > err || sol[i]-mval[i] < -1 * err)
                tobreak = false;
            if(isnan(sol[i]))
                return 2;
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
    return -1;
}

inline int solveEquations(std::vector<interval_arithmetic::Interval<double>> & result, 
interval_arithmetic::Interval<double> (*fi_x)(const std::vector<interval_arithmetic::Interval<double>> & X, int n),
interval_arithmetic::Interval<double> (*dfi_x)(const std::vector<interval_arithmetic::Interval<double>> & X, int n), 
const std::vector<interval_arithmetic::Interval<double>> & start_solution, 
int max_iter = 100, double err = 1E-10, double omega = 1.0)
{

    auto omegaI = interval_arithmetic::Interval<double>(omega);

    int itNum = 0;
    auto sol = start_solution;
    while(itNum < max_iter)
    { 
        bool tobreak = true;     

        auto solleft = sol;
        auto solright = sol;

        for (int i = 0; i < sol.size(); i++)
        {
            solleft[i] = sol[i].a;
            solright[i] = sol[i].b;
        }

        for (int i = 0; i < sol.size(); i++)
        {
            try{
                auto a = solleft[i] - omegaI * fi_x(solleft, i) / dfi_x(solleft,i);
                auto b = solright[i] - omegaI * fi_x(solright, i) / dfi_x(solright,i);

                sol[i].a = std::min(a.a, b.a);
                sol[i].b = std::max(a.b,b.b);
            }
            catch (std::exception & e)
            {
                    return 2;            
            }
            if(sol[i].b - sol[i].a > err)
                tobreak = false;
            if(isnan(sol[i].a) || isnan(sol[i].b))
                return 2;
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
    return -1;
}
