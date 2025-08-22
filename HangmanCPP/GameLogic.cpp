#include "GameLogic.h"  // Din egen header � kr�vs f�r att implementera klassen
#include <string>       //F�r att anv�nda string
#include <vector>       // F�r att anv�nda vector (motsvarande List<> i C#), vector �r value type inte reference type som List<> i C#
#include <cctype>       // f�r std::toupper
#include <algorithm>    // f�r std::transform
#include <thread>       // f�r std::this_thread::sleep_for
#include <windows.h>    // F�r att anv�nda SetConsoleTextAttribute (�ndra konsoltextf�rg)

using namespace std;

GameLogic::GameLogic(GameGraphics& graphics, WordGenerator& generator, Difficulty& diff)
    : gameGraphics(graphics), wordGenerator(generator), difficulty(diff) {
    // Konstruktor f�r GameLogic
}

void GameLogic::Game() {
    while (true) {
        int levelOfDifficulty = difficulty.ChooseGameDifficulty();
		string wordToGuess = wordGenerator.GetRandomWord(levelOfDifficulty);

        vector<char> guessedWord(wordToGuess.length(), '_');
		int lives = 6;                   // Antal liv
        vector<char> guessedLetters;     // Motsvarar "List<char> guessedLetters = new List<char>();"

        while (lives > 0 && guessedWord != vector<char>(wordToGuess.begin(), wordToGuess.end())) {
            system("cls");
			gameGraphics.MainGraphics();
			gameGraphics.ShowHangmanStatus(lives);
            cout << endl;

			cout << "\nWord: "; // Sktiver ut exempelvis "Ordet: __A_N"
            for (char c : guessedWord) {
                cout << c;
            }
            cout << endl;

			cout << "Guessed letters: "; // Skriver ut exempelvis "Gissade bokst�ver: A, N, E, B"
            for (size_t i = 0; i < guessedLetters.size(); ++i) {
                cout << static_cast<char>(toupper(guessedLetters[i]));
                if (i < guessedLetters.size() - 1)
                    cout << ", ";
            }
			cout << endl; // bryter raden med endl

			cout << "Lifes left: " << lives << endl;

			cout << "Guess a letter: ";
			string input; // Deklarera en str�ng f�r att lagra anv�ndarens inmatning
            getline(cin, input);  // Motsvarar Console.ReadLine()
            transform(input.begin(), input.end(), input.begin(), ::toupper); // G�r om till versaler (ToUpper)

			if (input.length() != 1 || !isalpha(input[0])) { // Kontrollera att inmatningen �r en enda bokstav
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // F�r att �ndra i konsollen (f�rg)
                SetConsoleTextAttribute(hConsole, 14);              // 14 = Gul
                cout << "Error input. Please only a single letter." << endl;
                SetConsoleTextAttribute(hConsole, 7);               // St�ller tillbaka,  7 = Standardf�rg
                this_thread::sleep_for(chrono::milliseconds(1500));
                continue; // Hoppar �ver resten av loopen och b�rjar om
			}

			char guess = input[0]; // Tar den f�rsta (och enda) bokstaven fr�n inmatningen

            if (guessedLetters.end() != find(guessedLetters.begin(), guessedLetters.end(), guess)) {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // F�r att �ndra i konsollen (f�rg)
                SetConsoleTextAttribute(hConsole, 14);              // 14 = Gul
                cout << "You have allready guessed letter " << guess << "." << endl;
                SetConsoleTextAttribute(hConsole, 7);               // St�ller tillbaka,  7 = Standardf�rg
                this_thread::sleep_for(chrono::milliseconds(1500));
                continue;   // Hoppar �ver resten av loopen och b�rjar om
			}

			guessedLetters.push_back(guess);                        // L�gger till gissningen i listan �ver gissade bokst�ver

            if (wordToGuess.end() != find(wordToGuess.begin(), wordToGuess.end(), guess)) {
                for (size_t i = 0; i < wordToGuess.length(); i++)
                {
                    if (wordToGuess[i] == guess)
                        guessedWord[i] = guess;
                }
				cout << "" << endl;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // F�r att �ndra i konsollen (f�rg)
				SetConsoleTextAttribute(hConsole, 10);              // 10 = Gr�n
				cout << "Correct!" << endl;
                SetConsoleTextAttribute(hConsole, 7);               // St�ller tillbaka,  7 = Standardf�rg
				this_thread::sleep_for(chrono::milliseconds(1500)); // Thread som sover i 1500 millisekunder (1,5 sekunder)
            }
            else {
				lives--;
				cout << "" << endl;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // F�r att �ndra i konsollen (f�rg)
				SetConsoleTextAttribute(hConsole, 12);              // 12 = R�d
                cout << "Wrong! You lose one life." << endl;
                SetConsoleTextAttribute(hConsole, 7);               // St�ller tillbaka,  7 = Standardf�rg
                this_thread::sleep_for(chrono::milliseconds(1500));
            }
		}

        if (guessedWord == vector<char>(wordToGuess.begin(), wordToGuess.end())) {
            system("cls");
            gameGraphics.MainGraphics();
            cout << "" << endl;
            gameGraphics.GraphicsLived();
            cout << "" << endl;

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // F�r att �ndra i konsollen (f�rg)
            SetConsoleTextAttribute(hConsole, 10);              // 10 = Gr�n
            cout << "Congrats!\nYou guessed the word: " << wordToGuess << "\n" << endl;
            SetConsoleTextAttribute(hConsole, 7);               // St�ller tillbaka,  7 = Standardf�rg
        }
        else {
			system("cls");
			gameGraphics.MainGraphics();
			cout << "" << endl;
			gameGraphics.ShowHangmanStatus(lives);
            cout << "" << endl;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // F�r att �ndra i konsollen (f�rg)
            SetConsoleTextAttribute(hConsole, 12);              // 12 = R�d
            cout << "Sorry, you loose. The word was: " << wordToGuess << "\n" << endl;
			SetConsoleTextAttribute(hConsole, 7);               // St�ller tillbaka,  7 = Standardf�rg
        }

        cout << "Want to play again? Y/N" << endl;
        string continueQuestion;
        getline(cin, continueQuestion);                         // Motsvarar Console.ReadLine()
        transform(continueQuestion.begin(), continueQuestion.end(), continueQuestion.begin(), ::toupper);
        if (continueQuestion == "Y") {
            continue;
        }
        else {
            cout << "Thanks for playing!" << endl;
            this_thread::sleep_for(chrono::milliseconds(1500));
            break;                                              // Avslutar spelet
		}
    }
}
