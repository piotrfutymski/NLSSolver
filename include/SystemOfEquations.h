#pragma once
#include "NonLinearFunction.h"

template <typename T>
class SystemOfEquations
{
public:

    SystemOfEquations(const std::vector<NonLinearFunction<T>> & eq);

    std::vector<NonLinearFunction<T>> getDer();

    std::vector<T> getDerFor(const std::vector<T> & val);

    std::vector<T> nextSolution(const std::vector<T> & val);

private:

    std::vector<NonLinearFunction<T>> _equations;

    std::vector<NonLinearFunction<T>> _derivatives;

    T _omega = 1;

private:

    void calculateDerivatives();


};

template <typename T>
SystemOfEquations<T>::SystemOfEquations(const std::vector<NonLinearFunction<T>> & eq)
{
    _equations = eq;
    this->calculateDerivatives();
}

template <typename T>
std::vector<NonLinearFunction<T>> SystemOfEquations<T>::getDer()
{ 
    return _derivatives;
}

template <typename T>
void SystemOfEquations<T>::calculateDerivatives()
{
    std::vector<NonLinearFunction<T>> res;
    res.resize(_equations.size());
    
    for (int i = 0; i < res.size(); i++)
            res[i] = _equations[i].getDerivative(i); 

    _derivatives = res;
}

template <typename T>
std::vector<T> SystemOfEquations<T>::getDerFor(const std::vector<T> & val)
{
    std::vector<T> res;
    res.resize(_equations.size());

    for (int i = 0; i < res.size(); i++)
            res[i] = _derivatives[i].getValueFor(val); 

    return res;
}

template <typename T>
std::vector<T> SystemOfEquations<T>::nextSolution(const std::vector<T> & val)
{
    std::vector<T> res;
    res.resize(_equations.size());
    auto mval = val;

    for (int i = 0; i < res.size(); i++)
    {
        res[i] = val[i] - _omega * _equations[i].getValueFor(mval) / _derivatives[i].getValueFor(mval); 
        mval[i] = res[i];
    }
        

    return res;

}