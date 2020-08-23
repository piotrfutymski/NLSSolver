#pragma once
#include <vector>
#include "../include/Interval.h"
struct APIs{
double (*f_x)(const std::vector<double> & X, int n);
double (*df_x)(const std::vector<double> & X, int n);
interval_arithmetic::Interval<double> (*fi_x)(const std::vector<interval_arithmetic::Interval<double>> & X, int n);
interval_arithmetic::Interval<double> (*dfi_x)(const std::vector<interval_arithmetic::Interval<double>> & X, int n);
};