#include <iostream>

/**
 * Prints the board!
 * This functions is used only for debug purposes
 *
 * @param board 2d array with the board state.
 * @param size  size of the board (size*size).
 */
void PrintBoard(int board[20][20], int size){
    std::cout << "\n";

    for (int j = 0; j<size; j++){
        for (int k = 0; k<size; k++){
            std::cout << board[j][k] << " ";
        }
        std::cout << "\n";
    }
}

/**
 * Makes the move in the choosed direction, if possible
 *
 * @param board 2d array with the board state.
 * @param size  size of the board (size*size).
 * @param direction  Direction of thr move 'u'p, 'd'own, 'r'ightnand 'l'eft.
 * @return bool - if the move changed anything in matrix.
 */
bool Move(int board[20][20], int size, char direction){
    
    return false;
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
