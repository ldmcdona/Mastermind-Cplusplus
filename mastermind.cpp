#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

//Boolean helper function that sorts a local copy of the users guess to check for repeat characters.
//Second for-loop added to ensure math characters don't slip past the stoi() check.
bool unique_string(string s){
    int l = s.length();
    sort(s.begin(), s.end());
    for(int i = 0; i < l-1; i++){
        if(s[i] == s[i+1]){
            return false;
        }
    }
    for(int i = 0; i < l; i++){
        if((int)s[i] > 57 || (int)s[i] < 48){
            //cout << "Invalid character " << s[i] << " detected.\nAscii value is: " << (int)s[i] << "\n";
            return false;
        }
    }
    return true;
}

//Main has 2 major parts. The setup, and the game itself.
//Both use while-loops with try-catch blocks to make sure they get valid inputs. 
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

    //This is the setup loop. It breaks when a pair of valid values are entered.
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

        //I really don't have exceptions memorized so I'm just using a blanket catch.
        } catch (...) {
            cout << "Please answer both questions with positive integers.\n";
        }
    }
    
    if(guesses == 0){
        guesses -= 1;
    }

    //Generating a random number with unique characters was a pain so we make a vector of all 10
    //single digit numbers and just shuffle it. Handy trick. 
    string combo;
    vector<char> base;
    char a;

    //Generate all the numbers, make them strings, add them to the vector. 
    for(int i = 0; i < 10; i++){
        a = '0' + i;
        base.push_back(a);
    }

    //Randomize the shuffle.
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(base.begin(), base.end(), default_random_engine(seed));

    //Collect the needed amount of random numbers.
    for(int i = 0; i < digits; i++){
        combo.push_back(base[i]);
    }

    //cout << "(Debug. Hidden number is: " << combo << " )\n";

    bool win = false;
    string temp;
    string guess;
    int match = 0;
    int close = 0;
    int value;
    int x;
    cout << "Hidden combination generated. Good luck!\n";

    //This is the actual game loop. Ends when 'guesses' equals zero or they guess correctly. 
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

        //Bit of a mess but basically:
        //Check to see if input is a number, run it through the 'unique_string' helper function,
        //make sure the guess is the correct length, then begin checking the guess for correctness.
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

                //All characters guessed that don't match the hidden number exactly are added to a string in
                //the above else condition and are then checked here to see if they feature in the hidden number.
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
            } else{
                cout << "Your guess has to be a " << digits << " digit number combination using each number only once.\n";
            }
        //Again, general catch-all, but with added 'Something went wrong.' message. 
        } catch(...){
            cout << "Something went wrong.\nYour guess has to be a " << digits << " digit number combination using each number only once. (Ex: '12345')\n";
        }
    }

    //Either they won or they didn't, either way the game is over.
    if(win){
        cout << "Congragulations! You guessed the secret number combination!\n";
    } else{
        cout << "Sorry, you ran out of guesses. Better luck next time!\n";
    }

    return 0;
}