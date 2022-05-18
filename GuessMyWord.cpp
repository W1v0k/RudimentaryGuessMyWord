// GuessMyWord.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <ctime>

//COLORS
#define RESET "\033[0m" //alb
#define RED  "\033[31m" 
#define GREEN "\033[32m"
#define CYAN    "\033[36m" 
#define YELLOW  "\033[33m" 

using namespace std;

int main()
{
    srand(time(0)); // foarte important ca sa mearga functia rand()
    bool gasit = 0;
    bool cuvTotal = 0; //Cand cuvantul a fost gasit in totalitate
    int tries = 10; //6 in mod normal
    string myWord;
    char* yourGuess;
    char yourLetter;
    char* guessLine; //linia de spanzuratoare _ _ _ _ _
    
    char wrongGuess[27]; //toate literele alfabetului maxim
    int dimWrongGuess = 0; // initial nu s-a gresit nimic
    
    char correctGuess[27]; //ghicite deja corect
    for (int i = 0; i < 27; i++)
    {
        correctGuess[i] = 0; //nu a fost ghicita nici o litera
    }
    int dejaGasit = 0; //nu am gasit candva o litera solutie
    
    vector<string> words;
    ifstream file("words.txt");
    string line;
    while (getline(file, line))
    {
        words.push_back(line);
    }
    myWord = words[rand() % words.size() + 1];
    
    yourGuess = new char[myWord.size()];
    guessLine = new char[myWord.size() * 2];

    //Initializarea liniei de spanzuratoare
    for (int i = 0; i < myWord.size()*2; ++i)
    {
        if (i % 2 == 0)
        {
            guessLine[i] = '_';
        }
        else
        {
            guessLine[i] = ' ';
        }
    }

    //cout << "Cuvantul meu este: " << myWord << "\n";
    /*
    for (int i = 0; i < myWord.size() * 2; ++i)
    {
        
        cout << guessLine[i];
    }
    */
    cout <<CYAN<< "Cuvantul meu are: " << myWord.size()<<" litere\n"<<RESET;
    cout << "Acum ghiceste literele cuvantului meu :p \n";

        do {
            gasit = 0;
                cout << "\nGhiceste litera:\n";
                yourLetter = tolower(getchar());
                getchar(); // prinde enterul
            
            for (int i = 0; i < myWord.length(); ++i)
            {
                int j = i * 2;
                if (myWord[i] == yourLetter)
                {
                    gasit = 1;
                    guessLine[j] = yourLetter;
                    yourGuess[i] = yourLetter;
                }
            }
            if (gasit == 1)
            {
                if (correctGuess[(int)yourLetter - 97] == 0)
                {
                    dejaGasit = 0; // o noua solutie
                    correctGuess[(int)yourLetter - 97] = 1;
                }
                else
                {
                    dejaGasit = 1; // am mai gasit candva acea solutie
                }
            }
            
            if (gasit == 0)
            {
                cout <<RED<< "Nu ai gasit litera!\n"<<RESET;
                tries--;
                wrongGuess[dimWrongGuess] = yourLetter;
                dimWrongGuess++;
                 for (int i = 0; i < myWord.length() * 2; ++i)
                 {
                    cout << guessLine[i];
                 }
            cout << endl;
            cout << YELLOW<< "Mai ai " << tries << " incercari! Ai grija!\n"<<RESET;
            cout << endl;
            cout << "Incercari gresite: ";
            for (int posWrong = 0; posWrong < dimWrongGuess; posWrong++)
            {
                cout << wrongGuess[posWrong];
            }
            cout << endl;
            }
            else if(gasit == 1 && !dejaGasit) 
            {
                cout << GREEN<<"Felicitari, ai ghicit o litera din cuvantul meu!\n"<<RESET;
                for (int i = 0; i < myWord.length() * 2; ++i)
                {
                    cout << guessLine[i];
                }
                cout << endl;
                if (dimWrongGuess) //daca s-a gresit candva
                {
                    cout << "\nIncercari gresite: \n";
                    for (int posWrong = 0; posWrong < dimWrongGuess; posWrong++)
                    {
                        cout << wrongGuess[posWrong];
                    }
                    cout << endl;
                }
            }
            else
            {
                cout << "Deja ai ghicit aceasta litera!\n";
            }
            for (int i = 0; i < myWord.length(); ++i)
            {
                if (myWord[i] != yourGuess[i])
                {
                cuvTotal = 0;
                break;
                }
                cuvTotal = 1;
            }

        } while (cuvTotal != 1 && tries);
        if (!tries)
        {
            cout << endl;
            cout <<RED<< "Imi pare rau, dar nu ai ghicit cuvantul! :( \n"<<RESET;
            cout <<CYAN<< "Cuvantul a fost: " <<RESET<< myWord << "\n";
        }
        else
        {
            cout << endl;
            cout <<GREEN<< "Felicitari! Ai invins spanzuratoarea! :) \n"<<RESET<<endl;
            cout <<CYAN<< "Ai aflat cuvantul meu: " <<RESET<< myWord << endl;
        }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
