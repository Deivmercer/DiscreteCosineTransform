//
// Created by David on 08/07/2024.
//

#include "utils.h"
#include <cstdlib>
#include <ctime>

std::vector<std::vector<int> > utils::creaMatrice(int size) {
    std::vector<std::vector<int> > matrice(size, std::vector<int>(size));
    unsigned seed = time(0);
    srand(seed);


    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrice[i][j] = rand() % 256;
        }
    }

    return matrice;
}
