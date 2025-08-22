#include "GameLogic.h"  // Din egen header – krävs för att implementera klassen
#include <string>       //För att använda string
#include <vector>       // För att använda vector (motsvarande List<> i C#), vector är value type inte reference type som List<> i C#
#include <cctype>       // för std::toupper
#include <algorithm>    // för std::transform
#include <thread>       // för std::this_thread::sleep_for
#include <windows.h>    // För att använda SetConsoleTextAttribute (ändra konsoltextfärg)

using namespace std;

GameLogic::GameLogic(GameGraphics& graphics, WordGenerator& generator, Difficulty& diff)
    : gameGraphics(graphics), wordGenerator(generator), difficulty(diff) {
    // Konstruktor för GameLogic
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

			cout << "Guessed letters: "; // Skriver ut exempelvis "Gissade bokstäver: A, N, E, B"
            for (size_t i = 0; i < guessedLetters.size(); ++i) {
                cout << static_cast<char>(toupper(guessedLetters[i]));
                if (i < guessedLetters.size() - 1)
                    cout << ", ";
            }
			cout << endl; // bryter raden med endl

			cout << "Lifes left: " << lives << endl;

			cout << "Guess a letter: ";
			string input; // Deklarera en sträng för att lagra användarens inmatning
            getline(cin, input);  // Motsvarar Console.ReadLine()
            transform(input.begin(), input.end(), input.begin(), ::toupper); // Gör om till versaler (ToUpper)

			if (input.length() != 1 || !isalpha(input[0])) { // Kontrollera att inmatningen är en enda bokstav
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // För att ändra i konsollen (färg)
                SetConsoleTextAttribute(hConsole, 14);              // 14 = Gul
                cout << "Error input. Please only a single letter." << endl;
                SetConsoleTextAttribute(hConsole, 7);               // Ställer tillbaka,  7 = Standardfärg
                this_thread::sleep_for(chrono::milliseconds(1500));
                continue; // Hoppar över resten av loopen och börjar om
			}

			char guess = input[0]; // Tar den första (och enda) bokstaven från inmatningen

            if (guessedLetters.end() != find(guessedLetters.begin(), guessedLetters.end(), guess)) {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // För att ändra i konsollen (färg)
                SetConsoleTextAttribute(hConsole, 14);              // 14 = Gul
                cout << "You have allready guessed letter " << guess << "." << endl;
                SetConsoleTextAttribute(hConsole, 7);               // Ställer tillbaka,  7 = Standardfärg
                this_thread::sleep_for(chrono::milliseconds(1500));
                continue;   // Hoppar över resten av loopen och börjar om
			}

			guessedLetters.push_back(guess);                        // Lägger till gissningen i listan över gissade bokstäver

            if (wordToGuess.end() != find(wordToGuess.begin(), wordToGuess.end(), guess)) {
                for (size_t i = 0; i < wordToGuess.length(); i++)
                {
                    if (wordToGuess[i] == guess)
                        guessedWord[i] = guess;
                }
				cout << "" << endl;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // För att ändra i konsollen (färg)
				SetConsoleTextAttribute(hConsole, 10);              // 10 = Grön
				cout << "Correct!" << endl;
                SetConsoleTextAttribute(hConsole, 7);               // Ställer tillbaka,  7 = Standardfärg
				this_thread::sleep_for(chrono::milliseconds(1500)); // Thread som sover i 1500 millisekunder (1,5 sekunder)
            }
            else {
				lives--;
				cout << "" << endl;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // För att ändra i konsollen (färg)
				SetConsoleTextAttribute(hConsole, 12);              // 12 = Röd
                cout << "Wrong! You lose one life." << endl;
                SetConsoleTextAttribute(hConsole, 7);               // Ställer tillbaka,  7 = Standardfärg
                this_thread::sleep_for(chrono::milliseconds(1500));
            }
		}

        if (guessedWord == vector<char>(wordToGuess.begin(), wordToGuess.end())) {
            system("cls");
            gameGraphics.MainGraphics();
            cout << "" << endl;
            gameGraphics.GraphicsLived();
            cout << "" << endl;

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // För att ändra i konsollen (färg)
            SetConsoleTextAttribute(hConsole, 10);              // 10 = Grön
            cout << "Congrats!\nYou guessed the word: " << wordToGuess << "\n" << endl;
            SetConsoleTextAttribute(hConsole, 7);               // Ställer tillbaka,  7 = Standardfärg
        }
        else {
			system("cls");
			gameGraphics.MainGraphics();
			cout << "" << endl;
			gameGraphics.ShowHangmanStatus(lives);
            cout << "" << endl;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // För att ändra i konsollen (färg)
            SetConsoleTextAttribute(hConsole, 12);              // 12 = Röd
            cout << "Sorry, you loose. The word was: " << wordToGuess << "\n" << endl;
			SetConsoleTextAttribute(hConsole, 7);               // Ställer tillbaka,  7 = Standardfärg
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
