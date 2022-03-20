#include <iostream>
#include <vector>
#include <algorithm>

class Game{
    public:
        int num;
        int best = 0;
        std::vector<std::vector<int>> t;
        Game(int number_of_rows) {
            this->num = number_of_rows;
        }

        int solve(){
            //acception
            for (int line = num -2; line>=0; line--) {
                for (int col = 0; col <= line; col++) {
                    t[line][col]=t[line][col] + std::max(t[line+1][col], t[line+1][col+1]);
                }
            }
            return t[0][0];
        }

        //DEBUG
        void printTriangle(){
            for(std::vector<std::vector<int>>::iterator i = t.begin(); i!=t.end(); i++){
                for(std::vector<int>::iterator j = (*i).begin(); j!=(*i).end(); j++){
                    std::cout << *j <<" ";
                }
                std::cout << "\n";
            }
        }

};

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int number_of_tests, number_of_rows;
    
    std::cin >> number_of_tests;
    for (int i=0; i<number_of_tests; i++) {

        std::cin >> number_of_rows;
        Game triangle(number_of_rows);
        for (int r=0; r<number_of_rows; r++) {
            std::vector<int> line (r+1);
            for (int c=0; c<r+1; c++) {

                std::cin >> line[c];
            
            }
            triangle.t.push_back(line);
        }
        std::cout << triangle.solve() << "\n";
    }

    return 0;
}