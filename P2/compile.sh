g++ -std=c++17 -Wall -Wextra -O2 main.cpp -lm
./a.exe < input1.txt > output1.txt
./a.exe < input2.txt > output2.txt

{ time ./a.exe < input1.txt ; } 2> time.txt

sleep 5;