#include "WordGenerator.h"  // Din egen header � kr�vs f�r att implementera klassen
#include <fstream>          // F�r att l�sa fr�n fil (ifstream) INKLUDETAR �ven <string> och <vector>
#include <random>           // F�r att slumpa ett ord
#include <algorithm>        // F�r std::transform
#include <cctype>           // F�r ::toupper
//#include <iostream>       // Beh�vs bara f�r cout och endl

using namespace std;

WordGenerator::WordGenerator() {
    filePath = "words.txt";
}

string WordGenerator::GetRandomWord(int difficulty) {

    switch (difficulty) {
    case 1: return GetEasyWordFromList();
    case 2: return GetNormalWordFromList();
    case 3: return GetHardWordFromList();
    default: return "Fel i GetRandomWord";
    }
}

string WordGenerator::GetEasyWordFromList() {

	auto words = ReadWordsFromFile();    //auto motsvarar "var" i C#
	vector<string> easyWords;           // Motsvarar "List<string>" i C#

	for (auto& word : words) {          // auto motsvarar "var" i C#, & �r pekare dvs ingen kopiering
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == 3)
			easyWords.push_back(word); //Motsvarar .Add() i C#
    }

    return PickSomeRandomWord(easyWords);
}

string WordGenerator::GetNormalWordFromList() {
    auto words = ReadWordsFromFile();
    vector<string> normalWords;

    for (auto& word : words) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == 4 || word.length() == 5)
            normalWords.push_back(word);
    }

    return PickSomeRandomWord(normalWords);
}

string WordGenerator::GetHardWordFromList() {
    auto words = ReadWordsFromFile();
    vector<string> hardWords;

    for (auto& word : words) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() >= 6)
            hardWords.push_back(word);
    }

    return PickSomeRandomWord(hardWords);
}

string WordGenerator::PickSomeRandomWord(const vector<string>& words) {
    if (words.empty()) return "NOWORDSFOUND";

    random_device rd; //ger ett slumpm�ssigt seed (startv�rde).
    mt19937 gen(rd()); // �r sj�lva generatorn (en Mersenne Twister � bra och snabb).
    uniform_int_distribution<> dist(0, words.size() - 1); // Skapar ett slumpintervall mellan 0 och antal ord - 1. (Allts� giltiga index i words)
    return words[dist(gen)]; // Anv�nder generatorn gen och intervallet dist f�r att h�mta ett slumpm�ssigt index. Returnerar ordet p� den platsen i listan.
}

vector<string> WordGenerator::ReadWordsFromFile() {
	vector<string> words; // Tom vektor f�r att lagra orden
	ifstream file(filePath); // �ppnar filen med ord
	string line; // Variabel f�r att l�sa varje rad

	while (getline(file, line)) { // L�ser filen rad f�r rad
		if (!line.empty()) // Kontrollera att raden inte �r tom
			words.push_back(line); // L�gger till raden i vektorn
    }

    return words;
}
