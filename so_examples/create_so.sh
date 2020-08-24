gcc -c -Wall -Werror -fpic testowy.cpp
gcc -shared -o  $1 testowy.o
rm testowy.o