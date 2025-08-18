#include "WordGenerator.h"
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <cctype>
#include <iostream>

WordGenerator::WordGenerator() {
    filePath = "words.txt";
}

std::string WordGenerator::GetRandomWord(int difficulty) {

    switch (difficulty) {
    case 1: return GetEasyWordFromList();
    case 2: return GetNormalWordFromList();
    case 3: return GetHardWordFromList();
    default: return "Fel i GetRandomWord";
    }
}

std::string WordGenerator::GetEasyWordFromList() {

    auto words = ReadWordsFromFile();
    std::vector<std::string> easyWords;

    for (auto& word : words) {
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == 3)
            easyWords.push_back(word);
    }

    return PickSomeRandomWord(easyWords);
}

std::string WordGenerator::GetNormalWordFromList() {
    auto words = ReadWordsFromFile();
    std::vector<std::string> normalWords;

    for (auto& word : words) {
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == 4 || word.length() == 5)
            normalWords.push_back(word);
    }

    return PickSomeRandomWord(normalWords);
}

std::string WordGenerator::GetHardWordFromList() {
    auto words = ReadWordsFromFile();
    std::vector<std::string> hardWords;

    for (auto& word : words) {
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() >= 6)
            hardWords.push_back(word);
    }

    return PickSomeRandomWord(hardWords);
}

std::string WordGenerator::PickSomeRandomWord(const std::vector<std::string>& words) {
    if (words.empty()) return "NOWORDSFOUND";

    std::random_device rd; //ger ett slumpmässigt seed (startvärde).
    std::mt19937 gen(rd()); // är själva generatorn (en Mersenne Twister – bra och snabb).
    std::uniform_int_distribution<> dist(0, words.size() - 1); // Skapar ett slumpintervall mellan 0 och antal ord - 1. (Alltså giltiga index i words)
    return words[dist(gen)]; // Använder generatorn gen och intervallet dist för att hämta ett slumpmässigt index. Returnerar ordet på den platsen i listan.
}

std::vector<std::string> WordGenerator::ReadWordsFromFile() {
	std::vector<std::string> words; // Tom vektor för att lagra orden
	std::ifstream file(filePath); // Öppnar filen med ord
	std::string line; // Variabel för att läsa varje rad

	while (std::getline(file, line)) { // Läser filen rad för rad
		if (!line.empty()) // Kontrollera att raden inte är tom
			words.push_back(line); // Lägger till raden i vektorn
    }

    return words;
}
