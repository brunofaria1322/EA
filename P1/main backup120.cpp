#include <iostream>
#include <unordered_set>
 class BoardState{
    public:
        int moves;
        int board[20][20];
};

void PrintBoard(int board[20][20], int size);
void PrintSet (std::unordered_set<int> s){
    for (std::unordered_set<int>::iterator it = s.begin(); it != s.end(); it++) {
        std::cout << *it << ' ';
    }
}

class Game{
    public:
        int max_moves;
        int min_slides = 51;
        int board_size;
        char moves[4] = {'u', 'r', 'd', 'l'};
        BoardState initial_state;

        Game(BoardState init_state, int brd_size, int max_plays){
            board_size = brd_size;
            max_moves = max_plays;
            initial_state = init_state;
        }

        void solve(BoardState current){

            if (isSolved(current)) {
                if (min_slides > current.moves) { min_slides = current.moves; }
                return;
            }

            if (current.moves == max_moves || current.moves == min_slides - 1) { return; }
            
            BoardState temp;
            
            for (int i = 0; i < 4; i++) {
                temp = copyBoardState(current);
                temp = makeMove(temp, moves[i]);
                if (!isEqual(current, temp)) { solve(temp); }
            }
            
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

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int num_tests, board_size, max_moves;
    std::cin >> num_tests;

    std::unordered_set<int> values;     //set to figure out if initial board is possible. 
    int temp;

    for (int i = 0; i < num_tests; i++) {
        std::cin >> board_size;
        std::cin >> max_moves;

        BoardState initial_board;
        initial_board.moves=0;

        values.clear();

        for (int j = 0; j < board_size; j++) {
            for (int k = 0; k < board_size; k++) {
                std::cin >> temp;
                initial_board.board[j][k] = temp;

                if (temp != 0){

                    while (values.find(temp) != values.end()) {
                        values.erase(temp);
                        temp *= 2;
                    }
                    values.insert(temp);
                }
                
            }
        }
        
        if (values.size() > 1) {
            //std::cout << "no solution\n";
            std::cout << "no solution\n";  
        }
        else{
            Game game(initial_board, board_size, max_moves);

            game.solve(game.initial_state);
            game.min_slides > max_moves ? std::cout << "no solution\n" : std::cout <<  game.min_slides << "\n";  
        }
    }



    return 0;
}
