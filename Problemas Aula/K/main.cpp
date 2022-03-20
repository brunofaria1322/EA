#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <queue>


class London{
    public:

        London(int m, int n){
            this->m = m;
            this->n = n;
            
            this->links = std::vector(n, std::vector<int>());

            this->cap = std::vector(n, std::vector<int> (n, 1));
            this->parent = std::vector(n, -1);

            this->readLines();

            //this->printLinks();
        }

        int countMaxTrips(){
            int s = 0; t = n-1;
            int flowMax = 0;
            int fp, u, v;


            while(( fp = BFS(s, t) ) > 0){
                //std::cout << fp <<'\n';
                flowMax += fp;
                u = t;

                while(u != s){
                    v = parent[u];
                    cap[v][u] -= fp;
                    cap[u][v] += fp; 
                    u = v;
                }
            }
            return flowMax;
        }
        

    private:
        int m;  //number of streets
        int n;  //number of street junctions, intersections and/or dead ends

        int t = 1;
        std::vector<std::vector<int>> links;

        std::vector<std::vector<int>> cap;
        std::vector<int> parent;


        void readLines(){
            int start, end;

            for (int i = 0; i < m; i++){
                std::cin >> start;
                std::cin >> end;

                start--;
                end--;

                links[start].push_back(end);
                links[end].push_back(start);
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

        int BFS(int s, int t){
            for (int i = 0; i < n; i++){
                parent[i] = -1;
            }

            parent[s] = -2;

            std::queue< std::pair<int, int> > Q;
            Q.push({s, std::numeric_limits<int>::max()});

            int v, fv, fu;
            std::pair<int, int> temp;

            while(!Q.empty()){

                temp = Q.front();
                v = temp.first;
                fv = temp.second;
                Q.pop();

                for(int u : links[v]){
                    if (parent[u] == -1 && cap[v][u] > 0){
                        parent[u] = v;
                        fu = std::min(fv, cap[v][u]);
                        
                        //std::cout << "(" << v << ", " << u << ")\n";

                        if(u == t){
                            return fu;
                        }

                        Q.push({u, fu});
                    }
                }
            }

            return 0;
        }

};

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);


    int m;  //number of streets
    int n;  //number of street junctions, intersections and/or dead ends
    
    std::cin >> m;
    std::cin >> n;

    London london(m, n);

    std::cout << london.countMaxTrips() << "\n";

    return 0;
}