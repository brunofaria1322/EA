g++ -std=c++17 -Wall -Wextra -O2 main.cpp -lm
./a.exe < input100.txt > output.txt

{ time ./a.exe < input104.txt ; } 2> time.txt