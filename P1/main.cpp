//Snippet at https://git.dei.uc.pt/snippets/25

#include <iostream>

void PrintBoard(int board[20][20], int size){
    std::cout << "\n";

    for (int j = 0; j<size; j++){
        for (int k = 0; k<size; k++){
            std::cout << board[j][k] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int num_tests, board_size, max_moves;
    std::cin >> num_tests;


    for (int i=0; i<num_tests; i++){
        std::cin >> board_size;
        std::cin >> max_moves;

        int board[20][20];

        for (int j = 0; j<board_size; j++){
            for (int k = 0; k<board_size; k++){
                std::cin >> board[j][k];
            }
        }

        PrintBoard(board, board_size);
    }
    
    return 0;
}
