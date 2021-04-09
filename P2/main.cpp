#include <iostream>
#include <math.h> 


class ARC{
    public:
        int n, h, H;

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
        }

        
        int build(){

            //TODO: BOTTOM-UP
            
            
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

        ARC arc(n,h,H);
        
        std::cout << arc.build() << "\n";  
        
    }



    return 0;
}
