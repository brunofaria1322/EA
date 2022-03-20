#include <iostream>
#include <cmath>


class ZeManel{
    public:
        int number_of_nodes, max_links;
        float best = INFINITY;   //40 * 12 +1
        bool active[12] = {false};
        int link_counter[12] = {0};
        int distances [12][12] = {0};
        
        ZeManel(int n, int k){
            this->number_of_nodes=n;
            this->max_links=k;
        }
        
        float solve(){
            
            active[0] = true;
            rec(1, 0);
            
            return best;
        }

    private:
        void rec(int active_counter, float distance){
            if (distance >= best) {
                return;
            }
            if(active_counter == number_of_nodes){
                best = distance;
                return;
            }

            for (int i=0; i<number_of_nodes; i++){
                if (active[i] && link_counter[i] < max_links) {

                    for (int j = 0; j < number_of_nodes; j++) {
                        if (!active[j]) {
                            if (distances[i][j] > 0){
                                link_counter[i]++;
                                link_counter[j]++;
                                active[j] = true;

                                rec(active_counter+1, distance+distances[i][j]);
                                
                                link_counter[i]--;
                                link_counter[j]--;
                                active[j] = false;
                                
                            }
                            
                        }
                    }
                }
            }
        }
};

void printMat(int mat[12][12], int num){
    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            std::cout<<mat[i][j]<<' ';
        }
        std::cout<<'\n';
    }
    
}

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, k;
    while (std::cin >> n && std::cin >> m && std::cin >> k) {

        ZeManel ze(n,k);
        int node1, node2, dist;

        for (int i = 0; i < m; i++) {
            std::cin >> node1;
            std::cin >> node2;
            std::cin >> dist;

            ze.distances[node1-1][node2-1] = ze.distances[node2-1][node1-1] = dist;
        }

        //printMat(distances, n);

        ze.solve() == INFINITY ? std::cout << "NO WAY!\n" : std::cout << ze.best <<"\n";
    }

    return 0;
}