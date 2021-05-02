#include <iostream>
#include <vector>
#include <math.h> 


class ARC{
    public:
        int n, h, H;
        int counter = 0;
        std::vector<std::vector<int>> up;
        std::vector<std::vector<int>> down;

        /**
         * Constructor of the class
         *
         * @param n     number of blocks
         * @param h     height of blocks
         * @param H     room height
         */
        ARC(int n, int h, int H){
            this->n = n;
            this->h = h;
            this->H = H;

            up = std::vector( H , std::vector<int> (n, 0));
            down = std::vector( H , std::vector<int> (n, 0));
        }

        
        void build(){

            int start;
            if ((H-h)*2 < n-1){
                start = (H-h)*2;
            }
            else{
                start = n-1;
            }

            //down values
            for (int i = 0; i < 2; i++){    //first 2 lines are 1s (only 1 possibility)
                for (int j = 2 - i; j <= start - i; j++){    //starting on the 3rd space (minimum for a arc)
                    down[i][j] = 1;
                }
            }

            //up values
            up[0][0] = 1;
            up[1][1] = 1;

            counter = 1; //at [1][1]
            
            int temp = 0, number_ceil;

            //O(H)
            for (int i = 2; i <= H-h; i++){                     //lines till max height possible
                number_ceil = std::ceil((float) i/(h-1));

                //O(n)
                for (int j = number_ceil; j <= start - number_ceil; j++){       //starting on the 3rd space (minimum for a arc)
                    temp = 0;
                    
                    //DOWN
                    if(down[i - 1][j + 1] != 0){
                        temp = mod_add(down[i - 1][j], down[i - 1][j + 1]);
                    }
                    else{
                        temp = down[i - 1][j];
                    }
                    if(i - h >= 0){
                        temp = mod_sub(temp, down[i - h][j + 1]);
                    }

                    down[i][j] = temp;

                    //UP
                    if(number_ceil<=j && j<=i){
                        temp = 0;

                        if(up[i - 1][j] != 0){
                            if(up[i - 1][j - 1] != 0){
                                temp = mod_add(up[i - 1][j], up[i - 1][j - 1]);
                            }
                            else{
                                temp = up[i - 1][j];
                            }
                            if(i - h >= 0){
                                temp = mod_sub(temp, up[i - h][j - 1]);
                            }

                            up[i][j] = temp;
                        }
                        else{
                            up[i][j] = 1;
                        }

                        counter = mod_add(counter,mod_mul( up[i][j], down[i][j]));
                        

                    }
                }
            }
            //printMatrix(down);

            //printMatrix(up);

            
        }

    private:
        int mod = 1000000007;
        
        int mod_abs(int a) {
            return ((a % mod) + mod) % mod;
        }

        int mod_add(int a, int b) {
            return (mod_abs(a) + mod_abs(b)) % mod;
        }

        int mod_sub(int a, int b) {
            return mod_add(a, -b);
        }

        int mod_mul(int a, int b) {
            return ((long long int)(a) * (long long int)(b)) % (long long int)(mod);
        }


        void printMatrix(std::vector<std::vector<int>> mat){
            
            std::cout << "---------MAT---------\n";
            for (int i = H-1; i>-1; i--){
                for (int v : mat[i]){
                    std::cout << v << " ";
                }
                std::cout << "\n";
            }
        }

};


int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int t, n, h, H;
    std::cin >> t;      //number of test cases


    for (int i = 0; i < t; i++) {
        std::cin >> n;
        std::cin >> h;
        std::cin >> H;

        //if impossible
        if (H <= h || n < 3){
            std::cout << "0\n";  
        }
        else{
            ARC arc(n,h,H);
            arc.build();
            std::cout << arc.counter << "\n";  
        }
        
    }


    return 0;
}
