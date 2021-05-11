#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>


struct connection { 
    int POI_A;
    int POI_B;
    int distance; 
};

class Map{
    public:
        /**
         * Constructor of the class
         *
         * @param n     number of POIs
         */
        Map(int n, int m){
            this->n = n;

            connections = std::vector( n , std::vector<connection> ());

            this->low = std::vector(n, -1);
            this->dfs = std::vector(n, -1);
            this->inStack = std::vector(n, false);


            this->readConnections(m);
            //this->printConnections();

            //this->findCircuits();
            //this->printCircuits();

        }

        /**
         * O(n + m) runs every vertex (n) and every edge (m)
         * 
         */
        void findCircuits(){
            for (int i = 0; i< n ; i++){
                if (dfs[i] == -1){
                    this->Tarjan(i);
                }
            }
        }

        /**
         * Answer to question 1
         */
        int getNumberOfCircuits(){
            return circuits.size();
        }


        /**
         * Answer to question 2
         */
        int getNumberPOIsInLargestCircuit(){
            return largest_circuit_POIs_number;
        }

        /**
         * 
         * 
         */
        void findBikeLanes(){
            int bike_lane_length;
            
            this->set = std::vector(this->n, -1);
            this->rank = std::vector(this->n, -1);

            for (std::unordered_set<int> circuit : circuits ){
                std::vector< connection > edges;

                for(int v : circuit){
                    for(connection con : connections[v]){
                        if(circuit.find(con.POI_B) != circuit.end()){
                            edges.push_back(con);
                        }
                    }
                }

                std::sort(edges.begin(), edges.end(), [](const connection &a, const connection &b){
                    return a.distance < b.distance;
                });

                //printEdges(edges);

                bike_lane_length = this->Kruskal(circuit, edges);

                if (bike_lane_length > longest_bike_lane_length){
                    longest_bike_lane_length = bike_lane_length;
                }

                total_bike_lanes_length += bike_lane_length;
            }
        }

        /**
         * Answer to question 3
         */
        int getLongestBikeLaneLength(){
            return longest_bike_lane_length;
        }


        /**
         * Answer to question 4
         */
        int getTotalBikeLanesLength(){
            return total_bike_lanes_length;
        }

    private:
        int n;
        std::vector<std::vector<connection>> connections;

        // TARJAN
        int t = 1;
        std::vector<int> low;
        std::vector<int> dfs;

        std::stack<int> S;
        std::vector<bool> inStack;
        
        std::vector< std::unordered_set<int> > circuits;

        int largest_circuit_POIs_number = 0;

        //Kruskal
        std::vector<int> set;
        std::vector<int> rank;

        int longest_bike_lane_length = 0;
        int total_bike_lanes_length = 0;

        void readConnections(int num_connections){
            int A, B, D;
            for (int i=0; i<num_connections; i++){

                std::cin >> A;   //POI A
                std::cin >> B;   //POI B
                std::cin >> D;   //distance between POIA to POIB (one way)

                connections[A-1].push_back({A-1, B-1, D});
            }
        }

        void printConnections(){

            std::cout << "Connections:\n";
            
            int counter = 0;
            for (std::vector<connection> line : connections ){
                std::cout << counter << " ->\t";
                for ( connection con : line ) {
                    std::cout << con.POI_B << " - " << con.distance << '\t';
                }
                std::cout << '\n';
                counter++;
            }
            std::cout << '\n';

        }

        /**
         * Finds Strongly Connected Components
         *  
         */
        void Tarjan(int v){
            low[v] = t;
            dfs[v] = t;
            t++;

            S.push(v);
            inStack[v] = true;
            
            int w;
            for (connection con : connections[v]){
                w = con.POI_B;
                if(dfs[w]==-1){
                    this->Tarjan(w);

                    if(low[v]>low[w]){
                        low[v] = low[w];
                    }
                }
                else if (inStack[w] && low[v]>dfs[w]) {
                    low[v] = dfs[w];
                }
            }

            if (low[v] == dfs[v]){

                std::unordered_set<int> C;
                
                do{
                    w = S.top();
                    S.pop();
                    inStack[w] = false;

                    C.insert(w);

                }while ( w != v);
                
                if (C.size() > 1){
                    circuits.push_back(C);

                    if ( (int) C.size() > largest_circuit_POIs_number){
                        largest_circuit_POIs_number = C.size();
                    }
                }
            }

        }

        void printCircuits(){
            std::cout << "Circuits:\n";

            for (std::unordered_set<int> line : circuits ){
                for (int v : line ) {
                    std::cout << v << ' ';
                }
                std::cout << '\n';
            }
            std::cout << '\n';

        }
        
        bool compareConnections(const connection &a, const connection &b){
            return a.distance < b.distance;
        }

        int find_set(int a){

            if (this->set[a] != a){
                this->set[a] = find_set(this->set[a]);
            }
            return this->set[a];
        }

        void link(int a, int b){

            if (rank[a] > rank[b]){
                set[b] = a;
            }
            else{
                set[a] = b;
            }
            if (rank[a] == rank[b]){
                rank[b]++;
            }
        }

        /**
         * Finds Minimum Spanning Tree
         * 
         * @param edges -> sorted list with connectons in circuit
         *  
         */
        int Kruskal(std::unordered_set<int> circuit, std::vector< connection > edges){
            
            int lane_length = 0;
            int set_A, set_B;

            for( int v : circuit){
                //make_set(v)
                
                set[v] = v;
                rank[v] = 0;

            }

            // edges already sorted !!

            for ( connection con : edges ){
                set_A = find_set(con.POI_A);
                set_B = find_set(con.POI_B);

                if ( set_A != set_B ){
                    lane_length += con.distance;
                    link(set_A, set_B);
                }
            }

            return lane_length;
        }

        

        void printEdges( std::vector< connection > edges ){
            std::cout << "Edges:\n";

            for (connection con : edges ){
                std::cout << con.POI_A << " - " << con.POI_B << " : " << con.distance << '\n';
            }
            std::cout << '\n';

        }

        

};


void notPossible( int q ){
    for (int j = 0; j < q-1; j++){
        std::cout << "0 ";  
    }
    std::cout << "0\n";  //last one doesn't have space at end
}


int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int t, n, m, q;
    int num_of_circuits = 0;
    std::cin >> t;      //number of test cases


    for (int i = 0; i < t; i++) {
        std::cin >> n;  //number of POIs
        std::cin >> m;  //number of connections between POIs
        std::cin >> q;  //number of questions

        //if impossible
        if (n < 2){
            notPossible(q);
        }
        else{
            Map map(n,m);
            
            map.findCircuits();
            num_of_circuits = map.getNumberOfCircuits();

            if(num_of_circuits == 0){
                notPossible(q);
            }
            else{ 
                switch (q){

                    case 1:
                        std::cout << map.getNumberOfCircuits() << '\n';  
                        break;
                    case 2:
                        std::cout << map.getNumberOfCircuits() << ' ' <<  map.getNumberPOIsInLargestCircuit() << '\n'; 
                        break;
                    case 3:
                        map.findBikeLanes();
                        std::cout << map.getNumberOfCircuits() << ' ' <<  map.getNumberPOIsInLargestCircuit() << ' ' << map.getLongestBikeLaneLength() << '\n'; 
                        break;
                    case 4:
                        map.findBikeLanes();
                        std::cout << map.getNumberOfCircuits() << ' ' <<  map.getNumberPOIsInLargestCircuit() << ' ' << map.getLongestBikeLaneLength() << ' ' <<  map.getTotalBikeLanesLength() << '\n'; 
                        break;
                    
                    default:
                        std::cout << "Something's wrong!\n";
                        break;
                }
            }

        }
        
    }
    return 0;
}
