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
std::vector<int> DCT1(const std::vector<int> &vettore, int index) {

    int N = vettore.size();
    std::vector<int> vettorigno(N, 0.0);
    /*
     *  Non è necessario calcolare esplicitamente tutte le volte il prodotto scalare di wk
     *  con se stesso per capire quale valore mettere. È possibile essere più efficienti
     *  semplicemente controllando l’indice k.
     *  se k = 0, w0·w0 = N, altrimenti wk· wk = N/2
    */

    // N: Il numero totale degli elementi nella sequenza di input
    // k: indice della dct (preso da index (mi dice a che vettore siamo))

    for (int i = 0; i < N; ++i) {
        if (i == 0 && index == 0) {
            // dato che non voglio fare il controllo ogni volta conviene fare
            // l'operazione prima delle chiamata solo per questo indice
            vettorigno[i] = vettore[i] + 1000;
            // (cos(pi*k*((2*i) + 1)/2*N)) * vettore[i] / (N)
        } else {
            vettorigno[i] = vettore[i] + 1;
            // (cos(pi*k*((2*i) + 1)/2*N)) * vettore[i] / (N/2)
        }

        std::cout << std::to_string(vettorigno[i]) << " ";
    }
    std::cout << std::endl;
    return vettorigno;
}

//funzione per dct2
std::vector<std::vector<int> > utils::DCT2(const std::vector<std::vector<int> > &matrice) {
    int N = matrice.size();
    std::vector<std::vector<int> > new_matrix(N, std::vector<int>(N));

    std::cout << "APPLICO PER RIGHE" << std::endl;
    //applico dct1 per righe
    for (int i = 0; i < N; ++i) {
        std::vector<int> row_dct = DCT1(matrice[i], i);
        for (int j = 0; j < N; ++j) {
            new_matrix[i][j] = row_dct[j];
        }
    }

    std::cout << "INVERTO" << std::endl;
    //inverto righe e colonne. necessario per poter lavorare come fatto sopra
    std::vector<std::vector<int> > transposed(N, std::vector<int>(N, 0.0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            transposed[j][i] = new_matrix[i][j];
            std::cout << std::to_string(transposed[j][i]) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "APPLICO PER COLONNE" << std::endl;
    //applico dct1 per colonne
    for (int i = 0; i < N; ++i) {
        std::vector<int> col_dct = DCT1(transposed[i], i);
        for (int j = 0; j < N; ++j) {
            new_matrix[j][i] = col_dct[j];
        }
    }

    return new_matrix;
}
