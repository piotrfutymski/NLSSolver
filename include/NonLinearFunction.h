#pragma once
#include <vector>
#include <string>
#include <stdlib.h>

template<typename T>
struct FuncElement
{
    T mul;
    std::vector<int> _exponents;
};

template<typename T>
class NonLinearFunction
{
public:

    NonLinearFunction();

    NonLinearFunction(int n);

    NonLinearFunction(const std::vector<FuncElement<T>> & el);

    void addElement(const FuncElement<T> & el);

    //

    T getValueFor(const std::vector<T> & x);

    NonLinearFunction<T> getDerivative(int vNum);

private:

    std::vector<FuncElement<T>> _elements;

    int _variableCount;

};


template <typename T>
NonLinearFunction<T>::NonLinearFunction()
{
    _variableCount = 0;
}

template <typename T>
NonLinearFunction<T>::NonLinearFunction(int n)
{
    _variableCount = n;  
}

template <typename T>
NonLinearFunction<T>::NonLinearFunction(const std::vector<FuncElement<T>> & el)
{
    _variableCount = el[0]._exponents.size();
    _elements = el;  
}

template <typename T>
void NonLinearFunction<T>::addElement(const FuncElement<T> & el)
{
    if(el._exponents.size() != _variableCount)
        return;
    
    _elements.push_back(el);
}

template <typename T>
T NonLinearFunction<T>::getValueFor(const std::vector<T> & x)
{
    T res = 0;

    for(auto & el: _elements)
    {
        T elres = 1.0;
        for (int i = 0; i < x.size(); i++)
        {
            T v = 1.0;
            for (int j = 0; j < el._exponents[i]; j++)
            {
                v = v * x[i];
            }
            elres  = elres * v;
        }
        res = res + elres * el.mul;
    }
    return res;
}

template <typename T>
NonLinearFunction<T> NonLinearFunction<T>::getDerivative(int vNum)
{
    NonLinearFunction res{this->_variableCount};

    for(auto & el: _elements)
    {
        if(el._exponents[vNum] != 0)
        {
            auto nel = el;
            nel.mul = nel.mul * el._exponents[vNum];
            nel._exponents[vNum]--;

            res.addElement(nel);
        }
    }

    return res;
}


