#include <iostream>

bool visited[400][400];

int Moves (int x, int y, int num_of_moves){
    if (num_of_moves < 0){ return 0; }

    int counter = 0;
    if (visited[x+200][y+200] != true ) { 
        visited[x+200][y+200] = true;
        counter++;
    }

    return counter +
        Moves(x+2, y+1, num_of_moves-1) +
        Moves(x+2, y-1, num_of_moves-1) +
        Moves(x-2, y+1, num_of_moves-1) +
        Moves(x-2, y-1, num_of_moves-1) +
        Moves(x+1, y+2, num_of_moves-1) +
        Moves(x-1, y+2, num_of_moves-1) +
        Moves(x+1, y-2, num_of_moves-1) +
        Moves(x-1, y-2, num_of_moves-1);
}

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int number_of_knightss;
    std::cin >> number_of_knightss;

    int counter = 0;
    int x, y, moves;
    for (int i = 0; i<number_of_knightss; i++){

        std::cin >> x;
        std::cin >> y;
        std::cin >> moves;

        counter += Moves(x, y, moves);
    }

    std::cout << counter << '\n';
    

    return 0;
}