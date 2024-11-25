// Author: Esraa Emary Abd El-Salam
// ID: 20230054
// Section: S19
// TA: Ahmed Ihab
// Version: 1.0

/////////////////////////////////////////////// Headers ////////////////////////////////////////////////////////

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

using namespace std;

template<typename T>
class Word_Tic_Tac_Toe_Board : public Board<T> {
public:
    Word_Tic_Tac_Toe_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();
};

template<typename T>
class Word_Tic_Tac_Toe_Player : public Player<T> {
public:
    Word_Tic_Tac_Toe_Player(string name, T symbol);

    void getmove(int &x, int &y);
};

template<typename T>
class Word_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Word_Tic_Tac_Toe_Random_Player(T symbol);

    void getmove(int &x, int &y);
};


/////////////////////////////////////////////// Implementation ////////////////////////////////////////////////////////

template<typename T>
Word_Tic_Tac_Toe_Board<T>::Word_Tic_Tac_Toe_Board() {
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool Word_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || symbol == 0)) {
        if (symbol == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}

template<typename T>
void Word_Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n   ___________________\n";
        cout << i + 1 << "  " << "|  ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(1) << this->board[i][j] << "  |  ";
        }
    }
    cout << "\n   ___________________\n      1     2     3\n\n";
}

template<typename T>
bool Word_Tic_Tac_Toe_Board<T>::is_win() {

}

template<typename T>
bool Word_Tic_Tac_Toe_Board<T>::is_draw() {

}

template<typename T>
bool Word_Tic_Tac_Toe_Board<T>::game_is_over() {

}

template<typename T>
void Word_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y) {
    string dim1, dim2;
    cout << "\nPlease enter the row:";
    getline(cin, dim1);
    cout << "\nPlease enter the column:";
    getline(cin, dim2);
    while (true) {
        if (dim1.size() != 1 || dim2.size() != 1) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "\nPlease enter the column:";
            getline(cin, dim2);
            continue;
        }
        if (dim1[0] < 49 || dim1[0] > 57) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "\nPlease enter the column:";
            getline(cin, dim2);
            continue;
        }
        if (dim2[0] < 49 || dim2[0] > 57) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "\nPlease enter the column:";
            getline(cin, dim2);
            continue;
        }
        break;
    }
    x = stoi(dim1);
    y = stoi(dim2);
}

template<typename T>
Word_Tic_Tac_Toe_Player<T>::Word_Tic_Tac_Toe_Player(std::string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Word_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

template<typename T>
Word_Tic_Tac_Toe_Random_Player<T>::Word_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void checkPlayerType(string &playerType, int num) {
    cout << "What is player " << num << " type ?\n[1] Human.\n[2] Computer.\nChoice:";
    getline(cin, playerType);
    while (true) {
        if (playerType != "1" && playerType != "2") {
            cout << "Please enter a valid choice!\n\n";
            cout << "What is player " << num << " type ?\n[1] Human.\n[2] Computer.\nChoice:";
            getline(cin, playerType);
            continue;
        }
        return;
    }
}

char getChar() {
    string character;
    char c;
    cout << "Please enter a char:";
    getline(cin, character);
    while (true) {
        if (character.size() != 1) {
            cout << "Please enter a valid char:";
            getline(cin, character);
            continue;
        }
        if (character[0] < 65 || (character[0] > 90 && character[0] < 97) || character[0] > 122) {
            cout << "Please enter a valid char:";
            getline(cin, character);
            continue;
        }
        c = character[0];
        return c;
    }
}

/////////////////////////////////////////////// Main ////////////////////////////////////////////////////////

int main() {
    string player1Type, player2Type, player1Name, player2Name;
    char c;
    Player<char> *players[2];
    Word_Tic_Tac_Toe_Board<char> *gameBoard = new Word_Tic_Tac_Toe_Board<char>();

    cout << "<--------- Welcome To Word Tic Tac Toe --------->\n";
    checkPlayerType(player1Type, 1);                // Get info of player 1.
    cout << "Please enter Player 1 name:";
    getline(cin, player1Name);

    if (player1Type == "1") {
        c = getChar();
        players[0] = new Word_Tic_Tac_Toe_Player<char>(player1Name, c);
    } else {
        c = getChar();
        players[0] = new Word_Tic_Tac_Toe_Random_Player<char>(c);
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    cout << "Please enter Player 2 name:";
    getline(cin, player2Name);

    if (player2Type == "1") {
        c = getChar();
        players[1] = new Word_Tic_Tac_Toe_Player<char>(player2Name, c);
    } else {
        c = getChar();
        players[1] = new Word_Tic_Tac_Toe_Random_Player<char>(c);
    }

    GameManager<char> Pyramid_Tic_Tac_Toe_Game(gameBoard, players);
    Pyramid_Tic_Tac_Toe_Game.run();
    cout << "Thanks For Playing My Game :)";
}