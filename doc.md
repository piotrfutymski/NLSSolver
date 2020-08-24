## Rozwiązywanie układu równań nieliniowych uproszczoną metodą Newtona

### Zastosowanie
Funkcja służy do znalezienia jednego z rozwiązań układu równań nieliniowych.

### Opis metody
Używana metoda rozwiązanie problemu jest metodą iteracyjną. Obliczenia rozpoczynają się od wektora będącego rozwiązaniem początkowym. Następnie wykorzystywany jest wzór iteracyjny do wyznaczania kolejnego rozwiązania:<br />
<img src="https://latex.codecogs.com/gif.latex?x_{ij+1}=x_{ij}-\omega{f_{i}}(\mathbf{X})/\frac{\partial{f_i(\mathbf{X})}}{\partial{x_{i}}}" /><br />
Gdzie omega jest parametrem od 0 do 2, a funkcje to kolejne równania układu, pod warunkiem, że układ jest postaci<br /> <img src="https://latex.codecogs.com/gif.latex?f(\mathbf{X})=0" /><br />
Okazuje się, że ten wzór iteracyjny często jest szybko zbieżny i w wyniku otrzymuje się wektor zbliżony do jednego z rozwiązań równania.

### Wywołanie funkcji
```
int status = solveEquations(res, f_x, df_x, startSolution, 100, 1E-10, 1.0);
```

### Argumenty funkcji
Funkcja przyjmuje następujące argumenty:
```
// T - double lub Interval w zależności od funkcji
std::vector<T> & result // wektor przechowujący rozwiązanie - posiada on tyle wartości ile zostanie przekazanych za pomocą parametru start_solution
T (*f_x)(const std::vector<T> &, int) // wskaźnik do funkcji, która opisuje równania układu. Jako argument przyjmuje wektor argumentów i numer równania dla którego ma obliczyć wartość
T (*df_x)(const std::vector<T> &, int) // wskaźnik do funkcji, która opisuje pochodne równań układu. Jako argument przyjmuje wektor argumentów i numer równania dla którego ma obliczyć wartość
const std::vector<T> & start_solution // wektor będący rozwiązaniem od którego rozpocznie się proces iteracyjny
int max_iter  // maksymalna ilośc iteracji, którą wykona metoda
double err    // założona dokładność
double omega  // parametr omega
```
### Wynik funkcji
Funkcja przekazuje wynik poprzez pierwszy parametr wywołania i zwraca int, będący statusem wykonania:<br />
0 - brak błędów - wektor zawiera rozwiązanie problemu<br />
1 - błąd przekroczenia maksymalnej liczby iteracji<br />
2 - błąd obliczeniowy - dzielenie przez zero lub przedział zawierający 0 lub inna operacja matematyczna dająca w wyniku nan

### Treść funkcji

Wersja w zwykłej arytmetyce:

```
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
```
Wersja w arytmetyce interwałowj:
```
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
```

### Przykład użycia:

Dla układu równań: <br />
<img src="https://latex.codecogs.com/gif.latex?x^2+y-5=0" /><br />
<img src="https://latex.codecogs.com/gif.latex?x^2+y^2-7=0" /><br />
Zdefiniowanego w ten sposób:
```
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
```

W wyniku wywołania:
```
int status = solveEquations(res, f, df, {10;10}, 100, 1E-10, 1.0);
```
Otrzymamy wynik:<br />
x = 1.7320508075793621<br />
y = 1.9999999999909197<br />
Wynik są niemal równe dokładnemu rozwiązaniu:<br />
x = sqrt(3)<br />
y = 2<br />

W wyniku wywoałania

