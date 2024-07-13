#include <chrono>
#include <iostream>

#include "utils/utils.h"

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //CREO LA MATRICE
    std::vector<std::vector<double> > matrice = utils::creaMatrice(8);
    std::cout << "matrix: " << std::endl;
    for (int i = 0; i < matrice.size(); ++i) {
        std::cout << "[";
        for (int j = 0; j < matrice[i].size(); ++j) {
            std::cout << matrice[i][j] << ",";
        }
        std::cout << "],";
        std::cout << std::endl;
    }

    std::vector<std::vector<double> > data{
            {231, 32, 233, 161, 24, 71, 140, 245},
            {247, 40, 248, 245, 124, 204, 36, 107},
            {234, 202, 245, 167, 9, 217, 239, 173},
            {193, 190, 100, 167, 43, 180, 8, 70},
            {11, 24, 210, 177, 81, 243, 8, 112},
            {97, 195, 203, 47, 125, 114, 165, 181},
            {193, 70, 174, 167, 41, 30, 127, 245},
            {87, 149, 57, 192, 65, 129, 178, 228}
    };
    //INIZIO CRONOMETRO
    start = std::chrono::system_clock::now();

    //ESEGUO MIO DCT2
    std::vector<std::vector<double> > result = utils::DCT2(data);

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