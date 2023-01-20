#include <iostream>
#include <random>
#include <fstream>
#include "Economy.h"

using namespace std;

int main() {
    mt19937 randomEngine;

    char yesNo = ' ';
    cout << "Set custom seed? (Y/n)" << endl;
    unsigned long seed;
    while (tolower(yesNo) != 'y' && tolower(yesNo) != 'n') {
        cin >> yesNo;
        if (tolower(yesNo) == 'y') {
            cout << "Enter your seed: ";
            cin >> seed;
            randomEngine.seed(seed);
            break;
        } else if (tolower(yesNo) == 'n') {
            random_device rd;
            seed = rd();
            cout << "Your seed: " << seed << endl;
            randomEngine.seed(seed);
            break;
        }
    }

    string filename;

    cout << "Enter the name of the file from which you want to read the game config." << endl;
    cin >> filename;

    fstream f;
    f.open(filename, ios::in);

    if (!f) {
        cerr << "oops";
        exit(1);
    }

    Economy economy(&randomEngine, 200000, 10);

    while(true) {
        economy.cycle();

    }

    return 0;
}