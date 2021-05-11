#include <iostream>
#include <vector>
#include <stack> 


struct connection { 
    int POI; 
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

    private:
        int n;
        std::vector<std::vector<connection>> connections;

        // TARJAN
        int t = 1;
        std::vector<int> low;
        std::vector<int> dfs;

        std::stack<int> S;
        std::vector<bool> inStack;
        
        std::vector< std::vector<int> > circuits;

        int largest_circuit_POIs_number = 0;

        void readConnections(int num_connections){
            int A, B, D;
            for (int i=0; i<num_connections; i++){

                std::cin >> A;   //POI A
                std::cin >> B;   //POI B
                std::cin >> D;   //distance between POIA to POIB (one way)

                connections[A-1].push_back({B-1, D});
            }
        }

        void printConnections(){

            std::cout << "Connections:\n";
            
            int counter = 0;
            for (std::vector<connection> line : connections ){
                std::cout << counter << " ->\t";
                for ( connection con : line ) {
                    std::cout << con.POI << " - " << con.distance << '\t';
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
                w = con.POI;
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

                std::vector<int> C;
                
                do{
                    w = S.top();
                    S.pop();
                    inStack[w] = false;

                    C.push_back(w);

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

            for (std::vector<int> line : circuits ){
                for (int v : line ) {
                    std::cout << v << ' ';
                }
                std::cout << '\n';
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
                        std::cout << map.getNumberOfCircuits() << ' ' <<  map.getNumberPOIsInLargestCircuit()<< '\n'; 
                        break;
                    case 3:
                        std::cout << map.getNumberOfCircuits() << ' ' <<  map.getNumberPOIsInLargestCircuit()<< '\n'; 
                        break;
                    case 4:
                        std::cout << map.getNumberOfCircuits() << ' ' <<  map.getNumberPOIsInLargestCircuit()<< '\n'; 
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
