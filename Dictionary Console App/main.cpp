#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class Dictionary {
private:
    map<string, string> dictionary;

public:
    void searchWord();
    void addWord();
    void exit();
    void mainMenu();
    void saveToFile(const string& word, const string& meaning, const string& filename);
    void loadDictionary();
};

void gotoxy(short x, short y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawBox(int x, int y, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            gotoxy(x + j, y + i);
            if (i == 0 && j == 0) cout << "\xDA"; // top-left corner
            else if (i == 0 && j == width - 1) cout << "\xBF"; // top-right corner
            else if (i == height - 1 && j == 0) cout << "\xC0"; // bottom-left corner
            else if (i == height - 1 && j == width - 1) cout << "\xD9"; // bottom-right corner
            else if (i == 0 || i == height - 1) cout << "\xC4"; // horizontal line
            else if (j == 0 || j == width - 1) cout << "\xB3"; // vertical line
            else cout << " ";
        }
    }
}

int main() {
    Dictionary dict;
    dict.loadDictionary();
    system("cls");
    int i;
    string wlc = " WELCOME TO DICTIONARY APP ";
    gotoxy(6, 2);
    for (i = 0; i < 20; i++) {
        Sleep(100);
        cout << "\3";
    }
    for (i = 0; i < wlc.length(); i++) {
        Sleep(50);
        cout << wlc[i];
    }
    for (i = 0; i < 20; i++) {
        Sleep(100);
        cout << "\3";
    }
    dict.mainMenu();
    return 0;
}

void Dictionary::mainMenu() {
    system("cls");
    gotoxy(6, 6);
    cout << "\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2";
    gotoxy(6, 7);
    cout << "\xb2\xb2";
    gotoxy(6, 8);
    cout << "\t   1. Search Word";
    gotoxy(6, 9);
    cout << "\xb2\xb2";
    gotoxy(6, 10);
    cout << "\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2";

    gotoxy(45, 6);
    cout << "\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2";
    gotoxy(45, 7);
    cout << "\xb2\xb2";
    gotoxy(45, 8);
    cout << "\t   2. Add Word";
    gotoxy(45, 9);
    cout << "\xb2\xb2";
    gotoxy(45, 10);
    cout << "\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2";

    gotoxy(29, 17);
    cout << "\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2";
    gotoxy(29, 18);
    cout << "\xb2\xb2";
    gotoxy(29, 19);
    cout << "\t 3. Exit";
    gotoxy(29, 20);
    cout << "\xb2\xb2";
    gotoxy(29, 21);
    cout << "\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2";

    gotoxy(20, 23);
    cout << "Enter your choice: ";
    char choice = _getch();

    switch (choice) {
        case '1':
            searchWord();
            break;
        case '2':
            addWord();
            break;
        case '3':
            exit();
            break;
        default:
            cout << "\aInvalid Input!";
            Sleep(1000);
            mainMenu();
    }
}

void Dictionary::searchWord() {
    system("cls");
    string word;
    gotoxy(6, 2);
    cout << "Search for a word in the dictionary";
    gotoxy(6, 4);
    cout << "Enter the word to search: ";
    cin >> word;

    ifstream file("database.csv");
    if (!file.is_open()) {
        gotoxy(6, 6);
        cout << "Unable to open file: database.csv";
        gotoxy(6, 8);
        cout << "Press any key to continue...";
        _getch();
        mainMenu();
        return;
    }

    string line, foundWord, meaning;
    bool wordFound = false;
    while (getline(file, line)) {
        istringstream iss(line);
        if (getline(iss, foundWord, ',') && getline(iss, meaning)) {
            if (foundWord == word) {
                wordFound = true;
                break;
            }
        }
    }
    file.close();

    if (wordFound) {
        gotoxy(6, 6);
        cout << "Word found:";

        // Calculate box dimensions
        int boxWidth = word.length() + meaning.length() + 10; // +10 for padding and separator
        int boxHeight = 3;

        // Draw the box
        drawBox(6, 7, boxWidth, boxHeight);

        // Display word and meaning inside the box
        gotoxy(8, 8);
        cout << left << setw(word.length() + 2) << word << ": " << meaning;

        gotoxy(6, 11);
        cout << "Is this meaning correct? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            gotoxy(6, 13);
            cout << "Enter the correct meaning: ";
            cin.ignore();
            string newMeaning;
            getline(cin, newMeaning);
            saveToFile(word, newMeaning, "errors.csv");
            gotoxy(6, 15);
            cout << "Corrected meaning saved to errors.csv";
        }
    }
    else {
        gotoxy(6, 6);
        cout << "Word not found in the dictionary.";
    }

    gotoxy(6, 17);
    cout << "Press any key to continue...";
    _getch();
    mainMenu();
}

void Dictionary::addWord() {
    system("cls");
    string word, meaning;
    gotoxy(6, 2);
    cout << "Add a new word to the dictionary";
    gotoxy(6, 4);
    cout << "Enter the word: ";
    cin >> word;
    gotoxy(6, 6);
    cout << "Enter the meaning: ";
    cin.ignore();
    getline(cin, meaning);

    dictionary[word] = meaning;
    saveToFile(word, meaning, "newwords.csv");

    gotoxy(6, 8);
    cout << "Word added successfully!";
    Sleep(1000);
    mainMenu();
}

void Dictionary::exit() {
    system("cls");
    gotoxy(20, 10);
    cout << "Thank you for using the Dictionary App!";
    gotoxy(20, 12);
    cout << "Exiting in 3 seconds...";
    Sleep(3000);
    exit();
}

void Dictionary::saveToFile(const string& word, const string& meaning, const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << word << "," << meaning << endl;
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void Dictionary::loadDictionary() {
    ifstream file("database.csv");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string word, meaning;
            if (getline(iss, word, ',') && getline(iss, meaning)) {
                dictionary[word] = meaning;
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: database.csv. Please check if the file exists and you have the correct permissions." << endl;
    }

    ifstream errorFile("errors.csv");
    if (errorFile.is_open()) {
        string line;
        while (getline(errorFile, line)) {
            istringstream iss(line);
            string word, meaning;
            if (getline(iss, word, ',') && getline(iss, meaning)) {
                dictionary[word] = meaning;
            }
        }
        errorFile.close();
    }
    else {
        cerr << "Unable to open file: errors.csv. Please check if the file exists and you have the correct permissions." << endl;
    }
}