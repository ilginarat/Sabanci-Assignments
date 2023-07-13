#include <iostream>
#include <string>
#include "strutils.h"
using namespace std;

bool checkIfAlpha(string word) {
    for (int i=0; i < word.length(); i++) {
        if (int(word[i])> int('z') || int(word[i]) < int('a')) {
            return false;
        }
    }
    return true;
}

void ifone(string word, int& live, string p2, string &output, bool &newMistake) {
    string guess;
    newMistake = false;
    cout << "Your guess: ";
    cin >> guess;
    ToLower(guess);
    
    if (checkIfAlpha(guess)) {

        if (guess==word) {
            output = word;
            live=0;
        }
        else {
            live-=1;
            newMistake = true;
        }
    }
    else {
        cout << "Invalid entry! Try again." << endl;
    }
}

void iftwo(string word, int& live, string& output, string& tried, bool &newMistake) {
    string guess;

    cout << "Your guess: ";
    cin >> guess;
    ToLower(guess);

    if (checkIfAlpha(guess) && guess.length() == 1)  {
        
        if (tried.find(guess)==string::npos) {
            newMistake = false;
            int i=0;
            int k=word.find(guess, i);

            if (k == string::npos) {
                live-=1;
                newMistake = true;
            }
            else {
                while (k != string::npos) {
                    output = output.substr(0,k) + guess + output.substr(k+1, output.length());
                    i=k+1;
                    k=word.find(guess, i);
                }
            }
            tried+=guess;
        }
        else {
            cout << "Guess entered before! Try again." << endl;
        }
    }
    else {
        cout << "Invalid entry! Try again." << endl;
    }
}


int main() {
    cout << "Welcome to the HANGMAN GAME" << endl << "---------------------------" << endl;
    string p1, p2, word, output, tried;
    int live;

    cout << "Player one, please enter your name: ";
    cin >> p1;
    cout << "Player two, please enter your name: ";
    cin >> p2;
    cout << "OK " << p1 <<" and " << p2 <<". Let's start the game!" << endl;
    cout << p1 <<", please input the word you want "<< p2 <<" to guess: ";
    cin >> word;
    
    ToLower(word);

    while (checkIfAlpha(word) == false) {
        cout << "Invalid word! Try again." << endl;
        cout << p1 <<", please input the word you want "<< p2 <<" to guess: ";
        cin >> word;
    }

        cout << p2 << ", you have 1 free guess, after that you will lose limbs!" << endl;

        tried="";
        output="";
        for (int i=0; i < word.length(); i++) {
            output.append("-");
        }
        live=6;
        while (live>0 && word != output) {
            string answer;
            cout << "The word is: "<< output << endl;
            cout << p2 <<", do you want to guess the word(1) or guess a letter(2)? " ;
            cin >> answer;
            
            while (!(answer == "1" || answer == "2")) {
                cout << "Invalid option!" << endl;
                cout << "The word is: "<< output << endl;
                cout << p2 <<", do you want to guess the word(1) or guess a letter(2)? " ;
                cin >> answer;
            }
            bool newMistake;
            if (answer == "1"){
                ifone(word, live, p2, output, newMistake);
            }

            else {
                iftwo(word, live, output, tried, newMistake);
            }

            if (newMistake) {
                if (live ==5) cout << "You have no free guess left." << endl;
                if (live ==4) cout << "You have lost a leg!"<< endl;
                if (live ==3) cout << "You have lost a leg!"<< endl;
                if (live ==2) cout << "You have lost an arm!"<< endl;
                if (live ==1) cout << "You have lost an arm!"<< endl;
            }
            
        }
    if (live == 0 && word != output) {
        cout << "You have lost a head! GAME OVER!" << endl;
        cout << p2 << " lost the game :(";
    }
        if (word == output) {
            cout << "The word is: "<< output << endl;
            cout << "Congratulations "<< p2 <<", you won!" << endl;
            cout << p2 <<" won the game!";
    }
    return 0;
}