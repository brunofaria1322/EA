#include <iostream>

int minimum_slides;

/**
 * Prints the board!
 * This functions is used only for debug purposes
 *
 * @param board 2d array with the board state.
 * @param size  size of the board (size*size).
 */
void PrintBoard(int board[20][20], int size) {
    std::cout << "\n";

    for (int j = 0; j < size; j++) {
        for (int k = 0; k < size; k++) {
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
 */
void Move(int board[20][20], int size, char direction) {
    switch (direction) {
    case 'u':
        for (int col = 0; col < size; col++) {
            int last = 0;
            for (int line = 1; line < size; line++) {
                if (board[line][col] == board[last][col] && board[last][col]) {
                    //merge
                    board[last][col] *= 2;
                    board[line][col] = 0;
                    last++;
                }
                else if (board[line][col] != board[last][col] && board[last][col] && board[line][col]) {
                    //diferent but no one is empty
                    if (last + 1 < line) {
                        //slide current to last+1
                        board[last + 1][col] = board[line][col];
                        board[line][col] = 0;
                    }
                    //else: cosecutive, so last takes current position
                    last++;
                }
                else if (!board[last][col] && board[line][col]) {
                    // last empty but current not (current slides to empty place)
                    board[last][col] = board[line][col];
                    board[line][col] = 0;
                }
            }
        }
        break;
    case 'r':
        for (int line = 0; line < size; line++) {
            int last = size - 1;
            for (int col = size - 2; col >= 0; col--) {
                if (board[line][col] == board[line][last] && board[line][last]) {
                    //merge
                    board[line][last] *= 2;
                    board[line][col] = 0;
                    last--;
                }
                else if (board[line][col] != board[line][last] && board[line][last] && board[line][col]) {
                    //diferent but no one is empty
                    if (last - 1 > col) {
                        //slide current to last+1
                        board[line][last - 1] = board[line][col];
                        board[line][col] = 0;
                    }
                    //else: cosecutive, so last takes current position
                    last--;
                }
                else if (!board[line][last] && board[line][col]) {
                    // last empty but current not (current slides to empty place)
                    board[line][last] = board[line][col];
                    board[line][col] = 0;
                }
            }
        }
        break;
    case 'd':
        for (int col = 0; col < size; col++) {
            int last = size - 1;
            for (int line = size - 2; line >= 0; line--) {
                if (board[line][col] == board[last][col] && board[last][col]) {
                    //merge
                    board[last][col] *= 2;
                    board[line][col] = 0;
                    last--;
                }
                else if (board[line][col] != board[last][col] && board[last][col] && board[line][col]) {
                    //diferent but no one is empty
                    if (last - 1 > line) {
                        //slide current to last+1
                        board[last - 1][col] = board[line][col];
                        board[line][col] = 0;
                    }
                    //else: cosecutive, so last takes current position
                    last--;
                }
                else if (!board[last][col] && board[line][col]) {
                    // last empty but current not (current slides to empty place)
                    board[last][col] = board[line][col];
                    board[line][col] = 0;
                }
            }
        }
        break;
    case 'l':
        for (int line = 0; line < size; line++) {
            int last = 0;
            for (int col = 1; col < size; col++) {
                if (board[line][col] == board[line][last] && board[line][last]) {
                    //merge
                    board[line][last] *= 2;
                    board[line][col] = 0;
                    last++;
                }
                else if (board[line][col] != board[line][last] && board[line][last] && board[line][col]) {
                    //diferent but no one is empty
                    if (last + 1 < col) {
                        //slide current to last+1
                        board[line][last + 1] = board[line][col];
                        board[line][col] = 0;
                    }
                    //else: cosecutive, so last takes current position
                    last++;
                }
                else if (!board[line][last] && board[line][col]) {
                    // last empty but current not (current slides to empty place)
                    board[line][last] = board[line][col];
                    board[line][col] = 0;
                }
            }
        }
        break;
    }
}

void CopyBoard(int board[20][20], int new_board[20][20], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            new_board[i][j] = board[i][j];
        }
    }
}

bool isEqual(int board[20][20], int new_board[20][20], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (new_board[i][j] != board[i][j]) { return false; }
        }
    }
    return true;
}

bool isSolved(int board[20][20], int size) {
    int numbers = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j]) { numbers++; }
            if (numbers > 1) { return false; }
        }
    }
    return true;
}

void BackTracking(int board[20][20], int size, int max_moves, int depth) {
    int new_board[20][20];

    /*
    //DEBUG
    std::cout <<"\n\t" << depth;
    PrintBoard(board, size);
    */

    if (isSolved(board, size)) {
        if (minimum_slides > depth) { minimum_slides = depth; }
        return;
    };

    if (depth >= max_moves) { return; }

    CopyBoard(board, new_board, size);
    Move(new_board, size, 'u');
    if (!isEqual(board, new_board, size)) { BackTracking(new_board, size, max_moves, depth + 1); }

    CopyBoard(board, new_board, size);
    Move(new_board, size, 'r');
    if (!isEqual(board, new_board, size)) { BackTracking(new_board, size, max_moves, depth + 1); }

    CopyBoard(board, new_board, size);
    Move(new_board, size, 'd');
    if (!isEqual(board, new_board, size)) { BackTracking(new_board, size, max_moves, depth + 1); }

    CopyBoard(board, new_board, size);
    Move(new_board, size, 'l');
    if (!isEqual(board, new_board, size)) { BackTracking(new_board, size, max_moves, depth + 1); }
}

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int num_tests, board_size, max_moves;
    std::cin >> num_tests;

    for (int i = 0; i < num_tests; i++) {
        std::cin >> board_size;
        std::cin >> max_moves;

        int board[20][20];
        minimum_slides = 51;

        for (int j = 0; j < board_size; j++) {
            for (int k = 0; k < board_size; k++) {
                std::cin >> board[j][k];
            }
        }

        /*
        //DEBUG
        PrintBoard(board, board_size);

        std::cout << "Up";
        Move(board, board_size, 'u');
        PrintBoard(board, board_size);

        std::cout << "Right";
        Move(board, board_size, 'r');
        PrintBoard(board, board_size);

        std::cout << "Down";
        Move(board, board_size, 'd');
        PrintBoard(board, board_size);

        std::cout << "Left";
        Move(board, board_size, 'l');
        PrintBoard(board, board_size);
        */

        BackTracking(board, board_size, max_moves, 0);

        minimum_slides <= max_moves ? std::cout << minimum_slides << "\n" : std::cout << "no solution\n";  
    }



    return 0;
}
