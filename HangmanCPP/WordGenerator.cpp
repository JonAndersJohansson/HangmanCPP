#include "WordGenerator.h"  // Din egen header – krävs för att implementera klassen
#include <fstream>          // För att läsa från fil (ifstream) INKLUDETAR även <string> och <vector>
#include <random>           // För att slumpa ett ord
#include <algorithm>        // För std::transform
#include <cctype>           // För ::toupper
//#include <iostream>       // Behövs bara för cout och endl

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

	for (auto& word : words) {          // auto motsvarar "var" i C#, & är pekare dvs ingen kopiering
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

    random_device rd; //ger ett slumpmässigt seed (startvärde).
    mt19937 gen(rd()); // är själva generatorn (en Mersenne Twister – bra och snabb).
    uniform_int_distribution<> dist(0, words.size() - 1); // Skapar ett slumpintervall mellan 0 och antal ord - 1. (Alltså giltiga index i words)
    return words[dist(gen)]; // Använder generatorn gen och intervallet dist för att hämta ett slumpmässigt index. Returnerar ordet på den platsen i listan.
}

vector<string> WordGenerator::ReadWordsFromFile() {
	vector<string> words; // Tom vektor för att lagra orden
	ifstream file(filePath); // Öppnar filen med ord
	string line; // Variabel för att läsa varje rad

	while (getline(file, line)) { // Läser filen rad för rad
		if (!line.empty()) // Kontrollera att raden inte är tom
			words.push_back(line); // Lägger till raden i vektorn
    }

    return words;
}
