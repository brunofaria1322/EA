#include <iostream>
#include <queue>

class BoardState{
    public:
        int moves;
        int board[20][20];
};

void PrintBoard(int board[20][20], int size);
void PrintQueue(std::queue<BoardState> q, int size);

class Game{
    public:
        int max_moves;
        int board_size;
        std::queue<BoardState> states;

        Game(BoardState initial_state, int brd_size, int max_plays){
            states.push(initial_state);
            board_size = brd_size;
            max_moves = max_plays;
        }

        int solve(){

            while (!states.empty())
            {
                BoardState current = states.front();
                
                states.pop();

                std::cout << "\n" << current.moves << "\t" << states.size();
                //PrintBoard(current.board, board_size);

                if (isSolved(current)) {
                    return current.moves;
                }

                if (current.moves < max_moves ) {            
                    BoardState temp = copyBoardState(current);
                    temp = makeMove(temp, 'u');

                    if (!isEqual(current, temp)) { states.push(temp); }

                    temp = copyBoardState(current);
                    temp = makeMove(temp, 'r');

                    if (!isEqual(current, temp)) { states.push(temp); }

                    temp = copyBoardState(current);
                    temp = makeMove(temp, 'd');

                    if (!isEqual(current, temp)) { states.push(temp); }

                    temp = copyBoardState(current);
                    temp = makeMove(temp, 'l');
                    
                    if (!isEqual(current, temp)) { states.push(temp); }
                }
            }
            
            return -1;
        }

        BoardState copyBoardState(BoardState previous){
            BoardState new_board;
            new_board.moves = previous.moves + 1;
            for (int i = 0; i < board_size; i++) {
                for (int j = 0; j < board_size; j++) {
                    new_board.board[i][j] = previous.board[i][j];
                }
            }
            return new_board;
        }

        bool isSolved(BoardState board) {
            int numbers = 0;

            for (int i = 0; i < board_size; i++) {
                for (int j = 0; j < board_size; j++) {
                    if (board.board[i][j]) { 
                        numbers++; 
                        if (numbers > 1) { 
                            return false; 
                        }
                    }
                }
            }
            return true;
        }


        bool isEqual(BoardState board, BoardState new_board) {
            for (int i = 0; i < board_size; i++) {
                for (int j = 0; j < board_size; j++) {
                    if (new_board.board[i][j] != board.board[i][j]) { return false; }
                }
            }
            return true;
        }


        /**
         * Makes the move in the choosed direction, if possible
         *
         * @param board BoardState.
         * @param direction  Direction of thr move 'u'p, 'd'own, 'r'ightnand 'l'eft.
         */
        BoardState makeMove(BoardState board, char direction) {
            switch (direction) {
                case 'u':
                    for (int col = 0; col < board_size; col++) {
                        int last = 0;
                        for (int line = 1; line < board_size; line++) {
                            if (board.board[line][col] == board.board[last][col] && board.board[last][col]) {
                                //merge
                                board.board[last][col] *= 2;
                                board.board[line][col] = 0;
                                last++;
                            }
                            else if (board.board[line][col] != board.board[last][col] && board.board[last][col] && board.board[line][col]) {
                                //diferent but no one is empty
                                if (last + 1 < line) {
                                    //slide current to last+1
                                    board.board[last + 1][col] = board.board[line][col];
                                    board.board[line][col] = 0;
                                }
                                //else: cosecutive, so last takes current position
                                last++;
                            }
                            else if (!board.board[last][col] && board.board[line][col]) {
                                // last empty but current not (current slides to empty place)
                                board.board[last][col] = board.board[line][col];
                                board.board[line][col] = 0;
                            }
                        }
                    }
                    break;
                case 'r':
                    for (int line = 0; line < board_size; line++) {
                        int last = board_size - 1;
                        for (int col = board_size - 2; col >= 0; col--) {
                            if (board.board[line][col] == board.board[line][last] && board.board[line][last]) {
                                //merge
                                board.board[line][last] *= 2;
                                board.board[line][col] = 0;
                                last--;
                            }
                            else if (board.board[line][col] != board.board[line][last] && board.board[line][last] && board.board[line][col]) {
                                //diferent but no one is empty
                                if (last - 1 > col) {
                                    //slide current to last+1
                                    board.board[line][last - 1] = board.board[line][col];
                                    board.board[line][col] = 0;
                                }
                                //else: cosecutive, so last takes current position
                                last--;
                            }
                            else if (!board.board[line][last] && board.board[line][col]) {
                                // last empty but current not (current slides to empty place)
                                board.board[line][last] = board.board[line][col];
                                board.board[line][col] = 0;
                            }
                        }
                    }
                    break;
                case 'd':
                    for (int col = 0; col < board_size; col++) {
                        int last = board_size - 1;
                        for (int line = board_size - 2; line >= 0; line--) {
                            if (board.board[line][col] == board.board[last][col] && board.board[last][col]) {
                                //merge
                                board.board[last][col] *= 2;
                                board.board[line][col] = 0;
                                last--;
                            }
                            else if (board.board[line][col] != board.board[last][col] && board.board[last][col] && board.board[line][col]) {
                                //diferent but no one is empty
                                if (last - 1 > line) {
                                    //slide current to last+1
                                    board.board[last - 1][col] = board.board[line][col];
                                    board.board[line][col] = 0;
                                }
                                //else: cosecutive, so last takes current position
                                last--;
                            }
                            else if (!board.board[last][col] && board.board[line][col]) {
                                // last empty but current not (current slides to empty place)
                                board.board[last][col] = board.board[line][col];
                                board.board[line][col] = 0;
                            }
                        }
                    }
                    break;
                case 'l':
                    for (int line = 0; line < board_size; line++) {
                        int last = 0;
                        for (int col = 1; col < board_size; col++) {
                            if (board.board[line][col] == board.board[line][last] && board.board[line][last]) {
                                //merge
                                board.board[line][last] *= 2;
                                board.board[line][col] = 0;
                                last++;
                            }
                            else if (board.board[line][col] != board.board[line][last] && board.board[line][last] && board.board[line][col]) {
                                //diferent but no one is empty
                                if (last + 1 < col) {
                                    //slide current to last+1
                                    board.board[line][last + 1] = board.board[line][col];
                                    board.board[line][col] = 0;
                                }
                                //else: cosecutive, so last takes current position
                                last++;
                            }
                            else if (!board.board[line][last] && board.board[line][col]) {
                                // last empty but current not (current slides to empty place)
                                board.board[line][last] = board.board[line][col];
                                board.board[line][col] = 0;
                            }
                        }
                    }
                    break;
            }
            return board;
        }
};

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

void PrintQueue(std::queue<BoardState> q, int size)
{
    int i=0;
    while (!q.empty())
    {
        BoardState t = q.front();
        std::cout << "queue " << i;
        std::cout << "\n" << t.moves;
        PrintBoard(t.board, size);
        q.pop();
        i++;
    }
    std::cout << std::endl;
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

        BoardState initial_board;
        initial_board.moves=0;

        for (int j = 0; j < board_size; j++) {
            for (int k = 0; k < board_size; k++) {
                std::cin >> initial_board.board[j][k];
            }
        }
        
        Game game(initial_board, board_size, max_moves);

        int min_slides = game.solve();
        std::cout << "sai";
        min_slides < 0 ? std::cout << "no solution\n" : std::cout << min_slides << "\n";  
    }



    return 0;
}
