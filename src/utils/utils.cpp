//
// Created by David on 08/07/2024.
//

#include "utils.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>

//creazione matrice
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

//funzione dct
std::vector<int> DCT1(const std::vector<int> &vettore, int size) {
    std::vector<int> vettorigno(size);
    for (int i = 0; i < size; ++i) {
        vettorigno[i] = vettore[i] + 1;
        std::cout << std::to_string(vettore[i]) << " ";
    }
    std::cout << std::endl;
    return vettorigno;
}

//funzione per dct2
std::vector<std::vector<int> > utils::DCT2(const std::vector<std::vector<int> > &matrice, int size) {
    std::vector<std::vector<int> > new_matrix(size, std::vector<int>(size));

    std::cout << "APPLICO PER RIGHE" << std::endl;
    //applico dct1 per righe
    for (int i = 0; i < size; ++i) {
        std::vector<int> row_dct = DCT1(matrice[i], size);
        for (int j = 0; j < size; ++j) {
            new_matrix[i][j] = row_dct[j];
        }
    }

    std::cout << "INVERTO" << std::endl;
    //inverto righe e colonne. necessario per poter lavorare come fatto sopra
    std::vector<std::vector<int> > transposed(size, std::vector<int>(size, 0.0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            transposed[j][i] = new_matrix[i][j];
            std::cout << std::to_string(transposed[j][i]) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "APPLICO PER COLONNE" << std::endl;
    //applico dct1 per colonne
    for (int i = 0; i < size; ++i) {
        std::vector<int> col_dct = DCT1(transposed[i], size);
        for (int j = 0; j < size; ++j) {
            new_matrix[j][i] = col_dct[j];
        }
    }

    return new_matrix;
}

//applicare dct su un vettore selzionato
