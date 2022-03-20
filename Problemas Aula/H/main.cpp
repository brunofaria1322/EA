#include <iostream>
#include <vector>
#include <queue>


class Data{
    public:
        int number_of_trains_and_stations, number_of_pairs;
        std::vector<std::vector<int>> neighbors;
        std::vector<int> colors;

        Data(int number_of_trains_and_stations, int number_of_pairs){
            this->number_of_trains_and_stations = number_of_trains_and_stations;
            this->number_of_pairs = number_of_pairs;

            neighbors = std::vector( number_of_trains_and_stations , std::vector<int> ());
            colors = std::vector<int> (number_of_trains_and_stations, -1);

            this->readConnections();
        }

        
        bool isCorrupted(){

            for(int i = 0; i< number_of_trains_and_stations; i++){
                if (colors[i] == -1 && !graphColoring(i)){
                    return true;
                }
            }

            return false;
        }

        /**
         * Graph Coloring (Needs to be possible to color the graph with only 2 colors
         * otherwise it is not "valid")
         * 
         * --BFS--
         * 
         * @return true if valid, false if not valid
         */
        bool graphColoring(int n){
            std::queue<int> q;
            q.push(n);

            colors[n] = 0;

            int v;
            while (!q.empty()){
                v = q.front();
                q.pop();

                for (int n : neighbors[v]){
                    if (colors[n] == -1){
                        colors[n] = 1 - colors[v];
                        q.push(n);
                    }
                    else if (colors[n] == colors[v]){
                        return false;
                    }
                }
            }

            return true;
            
        }
        
        void readConnections(){
            int p1, p2;

            for (int i=0; i<number_of_pairs; i++){
                std::cin >> p1;
                std::cin >> p2;

                neighbors[p1-1].push_back(p2-1);
                neighbors[p2-1].push_back(p1-1);
            }

            //printMat(neighbors);
        }

    private:
        void printMat(std::vector<std::vector<int>> mat){
            for(std::vector<std::vector<int>>::iterator i = mat.begin(); i!=mat.end(); i++){
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

    int number_of_trains_and_stations, number_of_pairs;
    
    while(std::cin >> number_of_trains_and_stations && std::cin >> number_of_pairs){
    
        Data data(number_of_trains_and_stations, number_of_pairs);  
        std::cout << (data.isCorrupted() ? "NO" : "NOT SURE") << "\n";
    }

    return 0;
}