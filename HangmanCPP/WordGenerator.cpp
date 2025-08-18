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

    std::random_device rd; //ger ett slumpm�ssigt seed (startv�rde).
    std::mt19937 gen(rd()); // �r sj�lva generatorn (en Mersenne Twister � bra och snabb).
    std::uniform_int_distribution<> dist(0, words.size() - 1); // Skapar ett slumpintervall mellan 0 och antal ord - 1. (Allts� giltiga index i words)
    return words[dist(gen)]; // Anv�nder generatorn gen och intervallet dist f�r att h�mta ett slumpm�ssigt index. Returnerar ordet p� den platsen i listan.
}

std::vector<std::string> WordGenerator::ReadWordsFromFile() {
	std::vector<std::string> words; // Tom vektor f�r att lagra orden
	std::ifstream file(filePath); // �ppnar filen med ord
	std::string line; // Variabel f�r att l�sa varje rad

	while (std::getline(file, line)) { // L�ser filen rad f�r rad
		if (!line.empty()) // Kontrollera att raden inte �r tom
			words.push_back(line); // L�gger till raden i vektorn
    }

    return words;
}
