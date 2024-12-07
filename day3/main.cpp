#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

int main(int argc, char** argv) {

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Unable to open the file.";
        return 1;
    }

    std::string input;
    std::string temp;
    std::regex pattern("(?:mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\))");
    long parte1 = 0;
    long parte2 = 0;
    long deveria_adicionar = 1;

    while(std::getline(inputFile, temp)) {
        input += temp;
    }

    std::sregex_iterator begin(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    for (std::sregex_iterator i = begin; i != end; i++) {
        std::smatch match = *i;
        std::string buffer = match.str();

        if (buffer.rfind("mul") == 0) {
            long a, b;
            a = std::stoi(match[1].str());
            b = std::stoi(match[2].str());
            parte1 += a * b;
            parte2 += a * b * deveria_adicionar;
        } else {
            if (buffer == "do()") {
                deveria_adicionar = 1;
            } else if (buffer == "don't()"){
                deveria_adicionar = 0;
            }
        }
    }

    std::cout << "Somatorio das multiplicacoes: " << parte1 << "\n";
    std::cout << "Somatorio das multiplicacoes levando em conta do e dont: " << parte2 << "\n";
    inputFile.close();
    return 0;
}