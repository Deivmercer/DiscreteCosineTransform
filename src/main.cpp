#include <chrono>
#include <iostream>

#include "utils/utils.h"

int main() {

    std::chrono::time_point<std::chrono::system_clock> start, end;

    //CREO LA MATRICE
    std::vector<std::vector<int>> matrice = utils::creaMatrice(10);

    /*for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << i << " x " << j << ": " << matrice[i][j] << std::endl;
        }
    }*/

    //INIZIO CRONOMETRO
    start = std::chrono::system_clock::now();

    //ESEGUO MIO DCT2
    std::vector<std::vector<int>> matrice2 = utils::creaMatrice(500);

    //FINE CRONOMETRO
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";


    //INIZIO CRONOMETRO

    //ESEGUO LIBRERIA DCT2

    //FINE CRONOMETRO

    return 0;
}
