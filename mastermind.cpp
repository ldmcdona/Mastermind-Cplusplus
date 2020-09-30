#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

bool unique_string(string s){
    int l = s.length();
    sort(s.begin(), s.end());
    for(int i = 0; i < l-1; i++){
        if(s[i] == s[i+1]){
            return false;
        }
    }
    return true;
}

int main(){
    cout << "Welcome to Mastermind.\n";
    cout << "Do you know how to play (y/n)?\n>";
    string tutorial;
    cin >> tutorial;

    if(tutorial == "n") {
        cout << "In this game you are trying to find the hidden number combination.\nEvery number in the combination is only used once.\nIf you guess a correct number in the wrong space the 'close' count will go up by one.\nIf you guess a correct number in the correct space the 'match' count will go up one.\n";
    }

    bool clear = true;
    int digits;
    int guesses;
    while (clear) {
        try {

            cout << "How many digits do you want the combination to be? (Between 2 and 9)\n>";
            cin >> digits;
            cout << "How many guesses do you want to have? (Enter 0 for unlimited)\n>";
            cin >> guesses;

            if(digits >= 2 && digits <= 9){
                clear = false;
            } else {
                cout << "The game can only be played with between 2 and 9 digits.\n";
            }

        } catch (...) {
            cout << "Please answer both questions with non-negative numbers.\n";
        }
    }
    
    if(guesses == 0){
        guesses -= 1;
    }

    string combo;
    vector<char> base;
    char a;

    for(int i = 0; i < 10; i++){
        a = '0' + i;
        base.push_back(a);
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(base.begin(), base.end(), default_random_engine(seed));

    for(int i = 0; i < digits; i++){
        combo.push_back(base[i]);
    }

    cout << "(Debug. Hidden number is: " << combo << " )\n";

    bool win = false;
    string temp;
    string guess;
    int match = 0;
    int close = 0;
    int value;
    int x;
    cout << "Hidden combination generated. Good luck!\n";

    while(guesses != 0 && win == false){

        if(guesses > 0 ){
            cout << "You have " << guesses << " guesses left.\n";
        }

        temp.clear();
        guess.clear();
        match = 0;
        close = 0;

        cout << "Guess: ";
        cin >> temp;

        try{
            value = stoi(temp);
            if(unique_string(temp) && temp.length() == digits){
                for(int i = 0; i < digits; i++){
                    if(temp[i] == combo[i]){
                        match++;
                    } else{
                        guess.push_back(temp[i]);
                    }
                }

                //cout << "(Debug. guess-array is " << guess << " combo-array is " << combo << ")\n";

                /* This loop is broken. */
                for(int i = 0; i < guess.length(); i++){
                    for(int j = 0; j < digits; j++){
                        //cout << "(Debug. " << guess[i] << " " << combo[j] << ")\n";
                        if(guess[i] == combo[j]){
                            close++;
                        }
                    }
                }

                if(match == digits){
                    win = true;
                }

                cout << "Close: " << close << ", Match: " << match << "\n";
                guesses--;
            }
        } catch(...){
            cout << "Something went wrong.\n";
        }
    }

    if(win){
        cout << "Congragulations! You guessed the secret number combination!\n";
    } else{
        cout << "Sorry, you ran out of guesses. Better luck next time!\n";
    }

    return 0;
}