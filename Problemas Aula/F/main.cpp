#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

class Wall{
    public:
        std::vector<int> objects_pos;
        int guard_range;

        int solve(){
            sort(objects_pos.begin(), objects_pos.end());

            std::vector<int> guards(1);

            guards[0]=(objects_pos[0] + guard_range);
            int g = 0;      //last guard position

            for (int i = 0;  i< (int) objects_pos.size(); i++){
                if (objects_pos[i] > guards[g] + guard_range){
                    guards.push_back(objects_pos[i] + guard_range);
                    g++;
                }
            }

            return g+1;
            
        }
        
        void readValues(){
            int number_of_objects, temp;

            std::cin >> number_of_objects;
            objects_pos = std::vector<int>(number_of_objects);

            std::cin >> this->guard_range;

            for (int i=0; i<number_of_objects; i++) {
                std::cin >> temp;
                objects_pos[i]=temp;
            }
             
        }

};

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int number_of_tests;
    
    std::cin >> number_of_tests;
    
    for (int i=0; i<number_of_tests; i++) {
        Wall wall;
        wall.readValues();
        std::cout << wall.solve() << "\n";
    }

    return 0;
}