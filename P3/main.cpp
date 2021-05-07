#include <iostream>
#include <vector>
#include <math.h> 


struct connection { 
    int POI; 
    int distance; 
};

class Map{
    public:
        int n;
        int counter = 0;
        std::vector<std::vector<connection>> connections;

        /**
         * Constructor of the class
         *
         * @param n     number of POIs
         */
        Map(int n, int m){
            this->n = n;

            connections = std::vector( n , std::vector<connection> ());

            this->readConnections(m);

            this->printConnections();
        }

        
        void build(){
            
        }

    private:

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

};


int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int t, n, m, q;
    std::cin >> t;      //number of test cases


    for (int i = 0; i < t; i++) {
        std::cin >> n;  //number of POIs
        std::cin >> m;  //number of connections between POIs
        std::cin >> q;  //number of questions

        //if impossible
        if (n < 2){
            for (int j = 0; j < q-1; j++){
                std::cout << "0 ";  
            }
            std::cout << "0\n";  //last one doesn't have space at end
        }
        else{
            Map map(n,m);
            
            switch (q){

                case 1:
                    /* code */
                    break;
                case 2:
                    /* code */
                    break;
                case 3:
                    /* code */
                    break;
                case 4:
                    /* code */
                    break;
                
                default:
                    std::cout << "Something's wrong!\n";
                    break;
            }
        }
        
    }


    return 0;
}
