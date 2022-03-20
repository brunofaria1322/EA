#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>


class Network{
    public:

        Network(int N){
            this->N = N;

            this->links = std::vector(N, std::vector<int>());

            this->low = std::vector(N, -1);
            this->dfs = std::vector(N, -1);
            this->parents = std::vector(N, -1);

            this->readLines();

            //this->printLinks();
            
        }

        int countCriticals(){

            this->AP(0);

            /*
            for ( int i : criticals){
                std::cout << i << " ";
            }
            std::cout <<"\n";
            */

            return criticals.size();
        }

        void AP(int v){
            low[v] = t;
            dfs[v] = t;
            t++;
            
            for (int w : links[v]){
                if(dfs[w]==-1){
                    parents[w] = v;
                    this->AP(w);

                    if(low[v]>low[w]){
                        low[v] = low[w];
                    }

                    if(( dfs[v] == 1 && dfs[w] != 2 ) || ( dfs[v] != 1 && low[w] >= dfs[v] ) ){
                        criticals.insert(v);
                    }
                }
                else if (parents[v]!=w && low[v]>dfs[w]) {
                    low[v] = dfs[w];
                }
            }
        }

    private:
        int N;  // number of places
        int t = 1;
        std::vector<std::vector<int>> links;

        std::vector<int> low;
        std::vector<int> dfs;
        std::vector<int> parents;

        std::unordered_set<int> criticals;


        void readLines(){

            std::string line;
            int start;
            int ends;

            while(std::getline(std::cin, line)  && line != "0"){

                std::stringstream ss(line);

                ss >> start;
                start--;

                while (ss >> ends) {
                    ends--;
                    links[start].push_back(ends);
                    links[ends].push_back(start);
                }
            }
        }

        void printLinks(){
            
            int counter = 0;
            for(std::vector<int> i : links){
                std::cout << counter << "->\t";

                for(int j : i){
                    std::cout << j << " ";
                }
                std::cout << "\n";

                counter ++;
            }

            std::cout << "\n";
        
        }   

};

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);


    int N;  //number of places
    
    while(std::cin >> N && N!=0){

        Network net(N);

        std::cout << net.countCriticals() << "\n";
    
    }

    return 0;
}