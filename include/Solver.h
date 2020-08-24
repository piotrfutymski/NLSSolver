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
        auto mval = sol;
        for (int i = 0; i < sol.size(); i++)
        {
            double cntr = (sol[i].a+ sol[i].b)/2.0;
            sol[i] = {cntr, cntr};
        }
        bool tobreak = true;     

        for (int i = 0; i < sol.size(); i++)
        {
            try{
                sol[i] = mval[i] - omegaI * fi_x(sol,i) / dfi_x(sol,i); 
            }
            catch (std::exception & e)
            {
                    return 2;            
            }
            if((sol[i].a - mval[i].a > err || sol[i].a-mval[i].a < -1 * err) ||
                (sol[i].b - mval[i].b > err || sol[i].b-mval[i].b < -1 * err))
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