#include <chrono>
#include <iostream>

#include "utils/utils.h"

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //CREO LA MATRICE
    std::vector<std::vector<double> > matrice = utils::creaMatrice(10);
    std::cout << "matrix: " << std::endl;
    for (int i = 0; i < matrice.size(); ++i) {
        for (int j = 0; j < matrice[i].size(); ++j) {
            std::cout << matrice[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //INIZIO CRONOMETRO
    start = std::chrono::system_clock::now();

    //ESEGUO MIO DCT2
    std::vector<std::vector<double> > result = utils::DCT2(matrice);

    //FINE CRONOMETRO
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    std::cout << std::endl;

    std::cout << "new matrix: " << std::endl;
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //INIZIO CRONOMETRO

    //ESEGUO LIBRERIA DCT2

    //FINE CRONOMETRO

    return 0;
}