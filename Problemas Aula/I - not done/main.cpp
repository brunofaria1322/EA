#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>


class Vacation{
    public:
        int number_of_places, last_place;
        std::vector<std::unordered_map<int,int>> links;
        std::vector<int> Q;

        Vacation(int number_of_places, int last_place){
            this->number_of_places = number_of_places;
            this->last_place = last_place-1;

            links = std::vector( number_of_places , std::unordered_map<int,int>());
            
            for(int i = 0; i<number_of_places; i++){
                Q.push_back(i);
            }

            this->readCosts();
        }

        
        int minimumPossibleCost(){
            
            std::vector<int> dist(number_of_places, std::numeric_limits<int>::max());
            dist[0] = 0;

            Q.erase(Q.begin());

            int u;
            while (!Q.empty()){

                std::cout<<"Q before: ";
                for(int i: Q){
                    std::cout<<i<<" ";
                }

                //gets closest from start and deletes from Q
                u = closest(0);

                std::cout<<"\nQ after: ";
                for(int i: Q){
                    std::cout<<i<<" ";
                }

                std::cout<<"\nGot: "<<u <<"\n";


                if (u == last_place){
                    break;
                }

                break;

                
            }
             

            return dist[last_place];
        }

    private:

        void readCosts(){
            int id, temp;
            for (int i=0; i<number_of_places; i++){
                std::cin >> id;

                for (int j=0; j<number_of_places; j++){

                    std::cin >> temp;
                    if(temp != -1 ){
                        links[id-1][j] = temp;
                    }
                }
            }

            printLinks();
        }

        int closest(int s){
            int min = std::numeric_limits<int>::max();
            int closest_i = -1;
            int closest_v = -1;

            
            for(size_t i = 0; i<Q.size(); i++){
                if (links[s].find(Q[i]) != links[s].end() && links[s][Q[i]] > 0 && links[s][Q[i]]<min){
                    min = links[Q[i]][s];

                    closest_i = i;
                    closest_v = Q[i];
                }
            }
            

            Q.erase(Q.begin()+closest_i);
            return closest_v;
        }

        void printLinks(){
            for(std::vector<std::unordered_map<int,int>>::iterator i = links.begin(); i!=links.end(); i++){
                for(std::unordered_map<int,int>::iterator j = (*i).begin(); j!=(*i).end(); j++){
                    std::cout << "("<< (*j).first <<", "<< (*j).second<<"), ";
                }
                std::cout << "\n";
            }
        }

};

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int number_of_places, last_place;
    
    while(std::cin >> number_of_places && std::cin >> last_place){
    
        Vacation trip(number_of_places, last_place);  
        std::cout << trip.minimumPossibleCost() << "\n";
    }

    return 0;
}