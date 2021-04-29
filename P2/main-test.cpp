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
            //TODO: BOTTOM-UP

            
            int start;
            if ((H-h)*2 < n-1){
                start = (H-h)*2;
            }

            //down values
            for (int i = 0; i < 2; i++){    //first 2 collumns are 1s (only 1 possibility)
                for (int j = 2 - i; j < n - i; j++){    //starting on the 3rd space (minimum for a arc)
                    down[i][j] = 1;
                }
            }
            
            int temp = 0;
            for (int i = 1; i<n-1; i++){    //lateral (room space)
                //if(i >= H){ break; }
                for (int j = 2; j <= (h-1) * i; j++){
                    if (j + h > H || j > (h-1)*(n-1 - i)){
                        break;
                    }
                    temp = 0;
                    for(int k = 1; k < h; k++){
                        if (j - k < 0){
                            break;
                        }
                        temp = mod_add(temp, down[j - k][n - i]);
                    }
                    down[j][n-1 - i] = mod_add(down[j][n-1 - i],  temp);
                }
            }
            printMatrix(down);

            up[0][0] = 1;
            
            temp = 0;
            for (int i = 1; i<n-1; i++){    //lateral (room space)
                if(i > H-h){ break; }
                for (int j = i; j <= (h-1) * i; j++){
                    if (j + h > H || j > (h-1)*(n-1 - i)){
                        break;
                    }
                    temp = 0;
                    for(int k = 1; k < h; k++){
                        if (j - k < 0){
                            break;
                        }
                        temp = mod_add(temp, up[j - k][i-1]);
                    }
                    up[j][i] = mod_add(up[j][i] , temp);

                    if(down[j][i] != 0){
                        counter = mod_add(counter,mod_mul( up[j][i], down[j][i]));
                    }
                }
            }

            printMatrix(up);

            
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

        // adapted from https://www.geeksforgeeks.org/how-to-avoid-overflow-in-modular-multiplication/
        int mod_mul(int a, int b)
        {
            int res = 0; // Initialize result
            
            while (b > 0)
            {
                // If b is odd, add 'a' to result
                if (b % 2 == 1)
                    res = mod_add(res, a);
        
                // Multiply 'a' with 2
                a = mod_add(a, a);
        
                // Divide b by 2
                b /= 2;
            }
        
            // Return result
            return res;
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

        //std::cout << n << ", "<< h << ", " << H << "\n";

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
