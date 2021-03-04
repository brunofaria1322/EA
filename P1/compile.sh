g++ -std=c++17 -Wall -Wextra -O2 main.cpp -lm
./a.exe < input.txt > output.txt

{ time ./a.exe < input100.txt ; } 2> time.txt

sleep 5;