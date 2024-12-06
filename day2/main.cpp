#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <string>

bool incrementandoOuDecrementando(std::vector<int>& vec) {
    if (vec.size() < 2) return true;

    bool incrementando = true;
    bool decrementando = true;

    for (size_t i = 1; i < vec.size(); ++i) {
        int diferenca = vec[i] - vec[i - 1];
        if (std::abs(diferenca) < 1 || std::abs(diferenca) > 3) {
            return false;
        }
        // Verifica padrões de monotonicidade
        if (diferenca <= 0) { 
            incrementando = false;
        }
        if (diferenca >= 0) {
            decrementando = false;
        }
    }

    return incrementando || decrementando;
}

bool podeSerValidaRemovendoUm(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::vector<int> copia = vec;
        copia.erase(copia.begin() + i);

        if (incrementandoOuDecrementando(copia)) {
            vec = copia;
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open the file.";
        return 1;
    }
    std::string linha;
    std::regex pattern("\\d+");
    int total_valido = 0;
   
    while(std::getline(inputFile, linha)) {
        std::sregex_iterator begin(linha.begin(), linha.end(), pattern);
        std::sregex_iterator end;

        std::vector<int> numbers;

        for (std::sregex_iterator i = begin; i != end; i++) {
            std::smatch match = *i;
            numbers.push_back(std::stoi(match.str()));
        }

        if (podeSerValidaRemovendoUm(numbers) || incrementandoOuDecrementando(numbers)) {
            total_valido++;
        }
        numbers.clear();
    }

    std::cout << total_valido << "\n";
    inputFile.close();
    return 0;
}