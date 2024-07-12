//
// Created by David on 08/07/2024.
//

#ifndef UTILS_H
#define UTILS_H

#include <vector>

namespace utils {
	//creazione matrice
	std::vector<std::vector<double>> creaMatrice(int size);
	//funzione per dct2
	std::vector<std::vector<double>> DCT2(const std::vector<std::vector<double>>& matrice);
}



#endif //UTILS_H
