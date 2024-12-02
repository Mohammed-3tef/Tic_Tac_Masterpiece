// Author: Esraa Emary Abd El-Salam
// ID: 20230054
// Section: S19
// TA: Ahmed Ihab
// Version: 2.0

/*
 * This is a simple implementation of the Pyramid Tic Tac Toe game.
 * The game is played on a 3x5 pyramid where each cell is filled with either 'X' or 'O'.
 * The game is played between two players:
    ** The first player has the symbol 'X'.
    ** The second player has the symbol 'O'.
 * The players take turns to place a number in an empty cell.
 * The player who places four symbols in a row, column, or diagonal loses the game.
 * The game ends in a draw if all cells are filled and no player wins.
*/

//--------------------------------------- HEADERS

#ifndef PYRAMID_TIC_TAC_TOE_H
#define PYRAMID_TIC_TAC_TOE_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- CLASSES

template<typename T>
class Pyramid_Tic_Tac_Toe_Board : public Board<T> {
private:
    bool over = false;
public:
    Pyramid_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template<typename T>
class Pyramid_Tic_Tac_Toe_Player : public Player<T> {
public:
    Pyramid_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
};

template<typename T>
class Pyramid_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Pyramid_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION

template<typename T>
Pyramid_Tic_Tac_Toe_Board<T>::Pyramid_Tic_Tac_Toe_Board() {
    this->rows = 3;
    this->columns = 5;
    int num = 1;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[num];
        for (int j = 2 - i; j < num + 2 - i; j++) {
            this->board[i][j] = 0;
        }
        num += 2;
    }
    this->n_moves = 0;
}

template<typename T>
bool Pyramid_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (((x == 0 && y == 2) || (x == 1 && y == 1) || (x == 1 && y == 2) || (x == 1 && y == 3) || (x == 2 && y == 0) ||
         (x == 2 && y == 1) || (x == 2 && y == 2) || (x == 2 && y == 3) ||
         (x == 2 && y == 4)) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}

template<typename T>
void Pyramid_Tic_Tac_Toe_Board<T>::display_board() {
    int num = 1;
    for (int i = 0; i < this->rows; i++) {
        if (i == 0) {
            cout << "\n            _____\n";
            cout << i + 1 << "           " << "| ";
            for (int j = 2 - i; j < num + 2 - i; j++) {
                cout << setw(1) << this->board[i][j] << " |";
            }
            cout << "\n        _____________\n";
        } else if (i == 1) {
            cout << i + 1 << "       " << "| ";
            for (int j = 2 - i; j < num + 2 - i; j++) {
                cout << setw(1) << this->board[i][j] << " | ";
            }
            cout << "\n    _____________________\n";
        } else {
            cout << i + 1 << "   " << "| ";
            for (int j = 2 - i; j < num + 2 - i; j++) {
                cout << setw(1) << this->board[i][j] << " | ";
            }
            cout << "\n    _____________________\n      1   2   3   4   5\n\n";
        }
        num += 2;
    }
}

template<typename T>
bool Pyramid_Tic_Tac_Toe_Board<T>::is_win() {                                   // Check winning.
    if ((this->board[0][2] != 0 && this->board[0][2] == this->board[1][2] && this->board[0][2] == this->board[2][2]) ||
        (this->board[0][2] != 0 && this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0]) ||
        (this->board[0][2] != 0 && this->board[0][2] == this->board[1][3] && this->board[0][2] == this->board[2][4]) ||
        (this->board[1][1] != 0 && this->board[1][1] == this->board[1][2] && this->board[1][1] == this->board[1][3]) ||
        (this->board[2][2] != 0 && this->board[2][2] == this->board[2][0] && this->board[2][2] == this->board[2][1]) ||
        (this->board[2][2] != 0 && this->board[2][2] == this->board[2][1] && this->board[2][2] == this->board[2][3]) ||
        (this->board[2][2] != 0 && this->board[2][2] == this->board[2][3] && this->board[2][2] == this->board[2][4])) {
        return true;
    }
    return false;
}

template<typename T>
bool Pyramid_Tic_Tac_Toe_Board<T>::is_draw() {
    if (this->n_moves == 9) return true;                                        // Check board is full.
    return false;
}

template<typename T>
bool Pyramid_Tic_Tac_Toe_Board<T>::game_is_over() {
    return over;
}

template<typename T>
void Pyramid_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y) {
    cout << "It's " << this->name << " turn\n";
    string dim1, dim2;
    cout << "\nPlease enter the row:";                                          // Get move.
    getline(cin, dim1);
    cout << "Please enter the column:";
    getline(cin, dim2);
    while (true) {                                                              // Check validity of move.
        if (dim1.size() != 1 || dim2.size() != 1) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "Please enter the column:";
            getline(cin, dim2);
            continue;
        }
        if (dim1[0] < 49 || dim1[0] > 57) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "Please enter the column:";
            getline(cin, dim2);
            continue;
        }
        if (dim2[0] < 49 || dim2[0] > 57) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "Please enter the column:";
            getline(cin, dim2);
            continue;
        }
        break;
    }
    x = stoi(dim1) - 1;                                                 // Set move.
    y = stoi(dim2) - 1;
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
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

#endif // PYRAMID_TIC_TAC_TOE_H