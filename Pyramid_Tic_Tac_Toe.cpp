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
class Pyramid_Tic_Tac_Toe_Board : public Board<T> {
public:
    Pyramid_Tic_Tac_Toe_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();
};

template<typename T>
class Pyramid_Tic_Tac_Toe_Player : public Player<T> {
public:
    Pyramid_Tic_Tac_Toe_Player(string name, T symbol);

    void getmove(int &x, int &y);
};

template<typename T>
class Pyramid_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Pyramid_Tic_Tac_Toe_Random_Player(T symbol);

    void getmove(int &x, int &y);
};


/////////////////////////////////////////////// Implementation ////////////////////////////////////////////////////////

template<typename T>
Pyramid_Tic_Tac_Toe_Board<T>::Pyramid_Tic_Tac_Toe_Board() {
    this->rows = 3;
    this->columns = 5;
    int num = 1;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[num];
        for (int j = 2 - i; j < num; j++) {
            this->board[i][j] = 0;
        }
        num += 2;
    }
    this->n_moves = 0;
}

template<typename T>
bool Pyramid_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {

}

template<typename T>
void Pyramid_Tic_Tac_Toe_Board<T>::display_board() {
    int num = 1;
    for (int i = 0; i < this->rows; i++) {
        if (i == 0) {
            cout << "\n            _____\n";
            cout << i + 1 << "           " << "| ";
            for (int j = 2 - i; j < num+ 2 - i; j++) {
                cout << setw(1) << this->board[i][j]<< " |";
            }
            cout << "\n        _____________\n";
        } else if (i == 1) {
            cout << i + 1 << "       " << "| ";
            for (int j = 2 - i; j < num +2 - i; j++) {
                cout << setw(1) << this->board[i][j] << " | ";
            }
            cout << "\n    _____________________\n";
        } else {
            cout << i + 1 << "   " << "| ";
            for (int j = 2 - i; j < num+ 2 - i; j++) {
                cout << setw(1) << this->board[i][j] << " | ";
            }
            cout << "\n    _____________________\n      1   2   3   4   5\n\n";
        }
        num += 2;
    }
}

template<typename T>
bool Pyramid_Tic_Tac_Toe_Board<T>::is_win() {

}

template<typename T>
bool Pyramid_Tic_Tac_Toe_Board<T>::is_draw() {

}

template<typename T>
bool Pyramid_Tic_Tac_Toe_Board<T>::game_is_over() {

}

template<typename T>
void Pyramid_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y) {

}

template<typename T>
Pyramid_Tic_Tac_Toe_Player<T>::Pyramid_Tic_Tac_Toe_Player(std::string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Pyramid_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

template<typename T>
Pyramid_Tic_Tac_Toe_Random_Player<T>::Pyramid_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
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

/////////////////////////////////////////////// Main ////////////////////////////////////////////////////////

int main() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    Pyramid_Tic_Tac_Toe_Board<char> *gameBoard = new Pyramid_Tic_Tac_Toe_Board<char>();

    cout << "<--------- Welcome To Pyramid Tic Tac Toe --------->\n";
    checkPlayerType(player1Type, 1);                // Get info of player 1.
    cout << "Please enter Player 1 name:";
    getline(cin, player1Name);

    if (player1Type == "1") {
        players[0] = new Pyramid_Tic_Tac_Toe_Player<char>(player1Name, 'X');
    } else {
        players[0] = new Pyramid_Tic_Tac_Toe_Random_Player<char>('X');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    cout << "Please enter Player 2 name:";
    getline(cin, player2Name);

    if (player2Type == "1") {
        players[1] = new Pyramid_Tic_Tac_Toe_Player<char>(player2Name, 'O');
    } else {
        players[1] = new Pyramid_Tic_Tac_Toe_Random_Player<char>('O');
    }

    GameManager<char> Pyramid_Tic_Tac_Toe_Game(gameBoard, players);
    Pyramid_Tic_Tac_Toe_Game.run();
    cout << "Thanks For Playing My Game :)";
}