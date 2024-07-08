#include <iostream>

#include "utils/utils.h"

int main() {

    std::vector<std::vector<int>> matrice = utils::creaMatrice(10);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << i << " x " << j << ": " << matrice[i][j] << std::endl;
        }
    }

    return 0;
}
