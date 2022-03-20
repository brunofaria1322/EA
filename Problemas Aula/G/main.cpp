#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

class Network{
    public:
        int number_of_members, number_of_connections;
        std::vector<std::vector<bool>> connections;

        int best = 0;
        std::vector<int> neighbor;

        Network(int number_of_members, int number_of_connections){
            this->number_of_members = number_of_members;
            this->number_of_connections = number_of_connections;

            connections = std::vector( number_of_members , std::vector<bool> (number_of_members, false));

            this->readConnections();
        }

        int find(){

            neighbor = std::vector<int>(number_of_members, 0);
            
            for (int i = 0; i<number_of_members; i++){
                rec(i, 1);
            }


            return best;
            
        }

        void rec(int i, int size){
            if (size > best){
                best = size;
            }
            if (i == number_of_members){
                return;
            }

            int ub = 0;
            for (int j = i+1; j < number_of_members; j++){
                if (neighbor[j] == 0){
                    ub ++;
                }
            }

            if (size + ub <= best){
                return;
            }

            for (int j  = i+1; j < number_of_members; j++){
                if (connections[i][j]){
                    neighbor[j] ++;
                }
            }

            for (int j  = i+1; j < number_of_members; j++){
                if (neighbor[j] == 0){
                    rec(j, size+1);
                }
            }

            for (int j  = i+1; j < number_of_members; j++){
                if (connections[i][j]){
                    neighbor[j] --;
                }
            }
        }
        
        void readConnections(){
            int p1, p2;

            for (int i=0; i<number_of_connections; i++){

                std::cin >> p1;
                std::cin >> p2;

                connections[p1][p2] = true;
                connections[p2][p1] = true;
            }
        }

};

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int number_of_members, number_of_connections;
    
    std::cin >> number_of_members;
    std::cin >> number_of_connections;
    
    Network net(number_of_members, number_of_connections);
    
    std::cout << net.find() << "\n";
    

    return 0;
}