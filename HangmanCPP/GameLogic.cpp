#include "GameLogic.h"
#include <string>
#include <vector>
#include <cctype>  // f�r std::toupper
#include <algorithm> // f�r std::transform
#include <thread>
#include <windows.h>


GameLogic::GameLogic(GameGraphics& graphics, WordGenerator& generator, Difficulty& diff)
    : gameGraphics(graphics), wordGenerator(generator), difficulty(diff) {
    // Konstruktor f�r GameLogic
}

void GameLogic::Game() {
    while (true) {
        int levelOfDifficulty = difficulty.ChooseGameDifficulty();
		std::string wordToGuess = wordGenerator.GetRandomWord(levelOfDifficulty);

        std::vector<char> guessedWord(wordToGuess.length(), '_');
		int lives = 6; // Antal liv
        std::vector<char> guessedLetters; /*List<char> guessedLetters = new List<char>();*/

        while (lives > 0 && guessedWord != std::vector<char>(wordToGuess.begin(), wordToGuess.end())) {
            system("cls");
			gameGraphics.MainGraphics();
			gameGraphics.ShowHangmanStatus(lives);
            std::cout << std::endl;

			std::cout << "\nWord: "; // Sktiver ut exempelvis "Ordet: __A_N"
            for (char c : guessedWord) {
                std::cout << c;
            }
            std::cout << std::endl;

			std::cout << "Guessed letters: "; // Skriver ut exempelvis "Gissade bokst�ver: A, N, E, B"
            for (size_t i = 0; i < guessedLetters.size(); ++i) {
                std::cout << static_cast<char>(std::toupper(guessedLetters[i]));
                if (i < guessedLetters.size() - 1)
                    std::cout << ", ";
            }
			std::cout << std::endl; // bryter raden med endl

			std::cout << "Lifes left: " << lives << std::endl;

			std::cout << "Guess a letter: ";
			std::string input; // Deklarera en str�ng f�r att lagra anv�ndarens inmatning
            std::getline(std::cin, input);  // Motsvarar Console.ReadLine()
            std::transform(input.begin(), input.end(), input.begin(), ::toupper); // G�r om till versaler (ToUpper)

			if (input.length() != 1 || !std::isalpha(input[0])) { // Kontrollera att inmatningen �r en enda bokstav
                std::cout << "Error input. Please only a single letter." << std::endl;
                continue; // Hoppar �ver resten av loopen och b�rjar om
			}

			char guess = input[0]; // Tar den f�rsta (och enda) bokstaven fr�n inmatningen

            if (guessedLetters.end() != std::find(guessedLetters.begin(), guessedLetters.end(), guess)) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14); // 14 = Gul
                std::cout << "You have allready guessed letter " << guess << "." << std::endl;
                SetConsoleTextAttribute(hConsole, 7);  // 7 = Standardf�rg
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                continue; // Hoppar �ver resten av loopen och b�rjar om
			}

			guessedLetters.push_back(guess); // L�gger till gissningen i listan �ver gissade bokst�ver

            if (wordToGuess.end() != std::find(wordToGuess.begin(), wordToGuess.end(), guess)) {
                for (size_t i = 0; i < wordToGuess.length(); i++)
                {
                    if (wordToGuess[i] == guess)
                        guessedWord[i] = guess;
                }
				std::cout << "" << std::endl;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 10); // 10 = Gr�n
				std::cout << "Correct!" << std::endl;
                SetConsoleTextAttribute(hConsole, 7);  // 7 = Standardf�rg
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            }
            else {
				lives--;
				std::cout << "" << std::endl;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 12); // 12 = R�d
                std::cout << "Wrong! You lose one life." << std::endl;
                SetConsoleTextAttribute(hConsole, 7);  // 7 = Standardf�rg
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            }
		}

        if (guessedWord == std::vector<char>(wordToGuess.begin(), wordToGuess.end())) {
            system("cls");
            gameGraphics.MainGraphics();
            std::cout << "" << std::endl;
            gameGraphics.GraphicsLived();
            std::cout << "" << std::endl;

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10); // 10 = Gr�n
            std::cout << "Congrats!\nYou guessed the word: " << wordToGuess << "\n" << std::endl;
            SetConsoleTextAttribute(hConsole, 7);  // 7 = Standardf�rg
        }
        else {
			system("cls");
			gameGraphics.MainGraphics();
			std::cout << "" << std::endl;
			gameGraphics.ShowHangmanStatus(lives);
            std::cout << "" << std::endl;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12); // 12 = R�d
            std::cout << "Sorry, you loose. The word was: " << wordToGuess << "\n" << std::endl;
			SetConsoleTextAttribute(hConsole, 7);  // 7 = Standardf�rg
        }

        std::cout << "Want to play again? Y/N" << std::endl;
        std::string continueQuestion;
        std::getline(std::cin, continueQuestion);  // Motsvarar Console.ReadLine()
        std::transform(continueQuestion.begin(), continueQuestion.end(), continueQuestion.begin(), ::toupper);
        if (continueQuestion == "Y") {
            continue;
        }
        else {
            std::cout << "Thanks for playing!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            break; // Avslutar spelet
		}
    }
}
