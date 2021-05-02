g++ -std=c++17 -Wall -Wextra -O2 main.cpp -lm
./a.exe < input.txt > output.txt
./a.exe < input1.txt > output1.txt
./a.exe < input2.txt > output2.txt
./a.exe < input3.txt > output3.txt


{ time ./a.exe < input.txt ; } 2> time.txt

sleep 5;