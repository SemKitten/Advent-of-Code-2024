#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <string>

int main(int argc, char** argv) {

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open the file.";
        return 1;
    }

    std::vector<int> numbers1;
    std::vector<int> numbers2;
    int number;

    std::string line;
    std::regex pattern("(\\d+)\\s+(\\d+)");
    while(std::getline(inputFile, line)) {
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            numbers1.push_back(std::stoi(match[1].str()));
            numbers2.push_back(std::stoi(match[2].str()));
        }
    }

    std::sort(numbers1.begin(), numbers1.end());
    std::sort(numbers2.begin(), numbers2.end());

    int quantidade_numeros;
    if (numbers1.size() == numbers2.size()) {
        quantidade_numeros = numbers1.size();
    } else {
        std::cerr << "Problems with given data.";
        inputFile.close();
        return 1;
    }

    std::vector<int> diferenca;

    int i = 0;
    int resultado_diferenca = 0;
    while(i < quantidade_numeros) {
        resultado_diferenca = abs(numbers1[i] - numbers2[i]);
        diferenca.push_back(resultado_diferenca);
        i++;
    }

    int total_diferenca = 0;
    for (int num : diferenca) {
        total_diferenca += num;
    }

    std::vector<int> similaridade;

    i = 0;
    int resultado_similaridade = 0;
    while (i < quantidade_numeros) {
        int numero_atual = numbers1[i];
        for (int num : numbers2) {
            if (numero_atual == num) {
                resultado_similaridade += 1;
            }
        }
        int conta = numero_atual * resultado_similaridade;
        similaridade.push_back(conta);
        resultado_similaridade = 0;
        i++;
    }

    int total_similaridade = 0;
    for (int num : similaridade) {
        total_similaridade += num;
    }

    std::cout << "Total da diferença: " << total_diferenca << "\n";
    std::cout << "Total da similaridade: " << total_similaridade << "\n";

    inputFile.close();
    return 0;
}