#pragma once
#include <string>
#include <vector>

class WordGenerator {
private:
    std::string filePath;

public:
    WordGenerator(); // Deklarerar konstruktorn
    std::string GetRandomWord(int difficulty);
    std::string GetEasyWordFromList();
    std::string GetNormalWordFromList();
    std::string GetHardWordFromList();

private:
    std::string PickSomeRandomWord(const std::vector<std::string>& words);
    std::vector<std::string> ReadWordsFromFile();
};
