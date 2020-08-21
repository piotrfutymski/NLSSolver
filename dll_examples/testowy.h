#pragma once
#include <vector>
//#include "../include/Interval.h"
struct APIs{
double (*f_x)(const std::vector<double> & X, int n);
double (*df_x)(const std::vector<double> & X, int n);
};