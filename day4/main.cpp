#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

int d_x[8] = { 0, 0, 1, -1, 1, -1, -1, 1 };
int d_y[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };

char letras[4] = { 'X', 'M', 'A', 'S'};

//i need to verify if its a letter
//then i need to verify if its xmas

int verificar_letra (std::vector<std::string>* input, char c, int x, int y) {

	if (x < 0 || y < 0 || x >= (*input).size() || y >= (*input).size()) {
        return 0;
    }
	return (*input)[x][y] == c;
}

int contar_xmas (std::vector<std::string>* input, int x, int y) {
    if((*input)[x][y] != 'X') {
        return 0;
    }

    int contador = 0;

    for (int i = 0; i < 8; i++) {
        if (verificar_letra(input, letras[1], x + d_x[i], y + d_y[i]) && verificar_letra(input, letras[2], x + (2 * d_x[i]), y + (2 * d_y[i])) && verificar_letra(input, letras[3], x + (3 * d_x[i]), y + (3 * d_y[i]))) {
            contador++;
        }
    }
    
    return contador;
}

int contar_crossmas(std::vector<std::string>* input, int x, int y) {
    if((*input)[x][y] != 'A') {
        return 0;
    }
    for(int i = 4; i < 6; i++) {
        if (verificar_letra(input, letras[1], x + d_x[i], y + d_y[i]) && verificar_letra(input, letras[3], x - d_x[i], y - d_y[i])) {
            if (verificar_letra(input, letras[1], x + d_x[i + 2], y + d_y[i + 2]) && verificar_letra(input, letras[3], x - d_x[i + 2], y - d_y[i + 2])) {
                return 1;
            }
            if (verificar_letra(input, letras[3], x + d_x[i + 2], y + d_y[i + 2]) && verificar_letra(input, letras[1], x - d_x[i + 2], y - d_y[i + 2])) {
                return 1;
            }
        }
    }

    return 0;
}

int main(int argc, char** argv) {

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open the file.";
        return 1;
    }
    
    std::vector<std::string> input;
    int contador_xmas = 0;
    int contador_crossmas = 0;

    while (true) {
        std::string line;
        std::getline(inputFile, line);
        if (line.empty()) {
            break;
        }
        input.push_back(line);
    }

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            contador_xmas += contar_xmas(&input, i, j);
            contador_crossmas += contar_crossmas(&input, i, j);
        }
    }

    std::cout << contador_xmas << "\n";
    std::cout << contador_crossmas << "\n";
    return 0;
}