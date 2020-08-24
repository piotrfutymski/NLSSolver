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

