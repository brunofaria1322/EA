#include <iostream>
#include <unordered_set>

bool CheckIfFair(std::unordered_set <int> men, std::unordered_set <int> women){
    std::unordered_set <int> ::iterator it, it2;
    for (it = men.begin(); it != men.end(); it++){
        for(it2 = std::next(it,1); it2 != men.end(); it2++){
            if ( women.find(*it + *it2) != women.end()){ return true; }
        }
    }

    for (it = women.begin(); it != women.end(); it++){
        for(it2 = std::next(it,1); it2 != women.end(); it2++){
            if ( men.find(*it + *it2) != men.end()){ return true; }
        }
    }
    return false;
}

int main() {
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int number_of_guests, number;

    while (std::cin >> number_of_guests){
        std::unordered_set <int> men;
        std::unordered_set <int> women;
        for (int i = 0; i< number_of_guests; i++){
            std::cin >> number;
            if (number > 0){
                women.insert(number);
            }
            else{
                men.insert(-number);
            }
        }
        std::cin >> number; // zero


        CheckIfFair(men, women) ? std::cout << "Fair\n": std::cout << "Rigged\n";
    }

    return 0;
}