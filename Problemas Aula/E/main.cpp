#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

class Pizzeria{
    public:
        int num;
        int sum = 0;
        std::vector<int> coocking_times;
        Pizzeria(int number_of_pizzas) {
            this->num = number_of_pizzas;
            
            this->readCookingTimes();
        }

        float solve(){
            int s = std::floor(sum / 2);
            std::vector<std::vector<bool>> mat;
            
            std::vector<bool> line (s + 1);
            line[0] = true;
            for (int i = 1; i < s + 1; i++){
                line[i] = false;
            }
            mat.push_back(line);
             
            for (int i = 1; i < num + 1; i++){
                std::vector<bool> line (s + 1);
                line[0] = true;

                mat.push_back(line);
            }
            for (int i = 1; i < num + 1; i++){
                for (int j = 1; j < s + 1; j++){
                    if(coocking_times[i-1] > j){
                        mat[i][j] = mat[i-1][j];
                    }
                    else{
                        mat[i][j] = mat[i-1][j] || mat[i-1][j-coocking_times[i-1]];
                    }

                }
            }

            int s1 = 0;
            for(int i=s; i>=0; i--){
                if (mat[num][i]){
                    s1 = i;
                    break;
                }
            }
            
            return (float) ((sum - s1) - s1)/100;

            
        }

    private:
        void printMat(std::vector<std::vector<bool>> mat){
            for(std::vector<std::vector<bool>>::iterator i = mat.begin(); i!=mat.end(); i++){
                for(std::vector<bool>::iterator j = (*i).begin(); j!=(*i).end(); j++){
                    std::cout << *j <<" ";
                }
                std::cout << "\n";
            }
        }
        void readCookingTimes(){
            coocking_times = std::vector<int>(num);
            float temp;
            const float eps = 0.001;                //for precision errors
            for(int i = 0; i < num; i++){
                std::cin >> temp;
                coocking_times[i] = (temp + eps) * 100;
                sum += coocking_times[i];
            }
        }
        void printCockingTimes(){
            for(std::vector<int>::iterator i = coocking_times.begin(); i!=coocking_times.end(); i++){
              std::cout << *i <<" ";
            }
            std::cout << "\n";
        }

};

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int number_of_pizzas;
    
    while(std::cin >> number_of_pizzas){
        Pizzeria p(number_of_pizzas);
        std::cout << p.solve() << "\n";
    }

    return 0;
}