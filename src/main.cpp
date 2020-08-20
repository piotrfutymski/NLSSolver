#include "Application.h"

wxIMPLEMENT_APP(Application);

/*
#include <iostream>
#include "Interval.h"
#include "SystemOfEquations.h"


int main(int, char**) {

    NonLinearFunction<double> a({   {1,{2,0}}, {1,{0,1}}, {-5,{0,0}}      });
    NonLinearFunction<double> b({   {1,{2,0}}, {1,{0,2}}, {-7,{0,0}}      }); 

    std::vector<NonLinearFunction<double>> eq;
    eq.push_back(a);
    eq.push_back(b);

    SystemOfEquations<double> sys(eq);

    std::vector<double> sol = {-10,10};

    for (int i = 0; i < 20; i++)
    {
        std::cout<< a.getValueFor(sol)<<"\t"<<b.getValueFor(sol)<<"\t\t\t";
        std::cout << sol[0]<<"\t"<< sol[1]<<"\n";
        sol = sys.nextSolution(sol);
    }
    

}
*/