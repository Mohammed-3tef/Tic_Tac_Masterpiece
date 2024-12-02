// Author: Nagham Wael Mohamed
// ID: 20231189
// Section: S19
// TA: Ahmed Ihab
// Version: 1.0

/*
 * This is a simple implementation of the Four In A Row game.
 * The game is played on a 3x3 board where each cell is filled with either 'X' or 'O'.
 * The game is played between two players:
    ** The first player has the symbol 'X'.
    ** The second player has the symbol 'O'.
 * The players take turns to place their symbol in an empty cell.
 * The player who places three symbols in a row, column, or diagonal loses the game.
 * The game ends in a draw if all cells are filled and no player wins.
*/

//--------------------------------------- HEADERS

#ifndef MISERE_TIC_TAC_TOE_H
#define MISERE_TIC_TAC_TOE_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- GLOBAL VARIABLES

string name1, name2;
int countNum = 0;

//--------------------------------------- CLASSES

template<typename T>
class Misere_Tic_Tac_Toe_Board : public Board<T> {
public:
    Misere_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void getNames(string namePlayer1, string namePlayer2);
};

template<typename T>
class Misere_Tic_Tac_Toe_Player : public Player<T> {
public:
    Misere_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
};

template<typename T>
class Misere_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Misere_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION

template<typename T>
void Misere_Tic_Tac_Toe_Board<T>::getNames(std::string namePlayer1, std::string namePlayer2) {
    name1 = namePlayer1;
    name2 = namePlayer2;
}

template<typename T>
// Constructor for X_O_Board
Misere_Tic_Tac_Toe_Board<T>::Misere_Tic_Tac_Toe_Board() { //the constructor here is where we initialize the board
    this->rows = this->columns = 3;    //3 rows and 3 columns to make the grid
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;   //initialized the board with zeros
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool Misere_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            countNum++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

template<typename T>
void Misere_Tic_Tac_Toe_Board<T>::display_board() {
    cout << "\n     1   2   3\n";
    cout << "   -------------\n";

    for (int i = 0; i < this->rows; i++) {
        cout << ' ' << i + 1 << " |";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << setw(1);

            if (this->board[i][j] == 0) cout << " ";
            else cout << this->board[i][j];

            cout << " |";
        }
        cout << "\n   -------------\n";
    }
    cout << endl;
}

template<typename T>
// Returns true if there is any winner
bool Misere_Tic_Tac_Toe_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] &&
             this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] &&
             this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template<typename T>
bool Misere_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool Misere_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template<typename T>
// Constructor for X_O_Player
Misere_Tic_Tac_Toe_Player<T>::Misere_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Misere_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y) {
    if (countNum % 2 == 0) this->name = name2;
    else this->name = name1;

    while (true) {
        cout << "Enter your move in this form(row space column,e.g 1 3): ";
        cin >> x >> y;

        // Convert to 0-based indexing
        x--; y--;

        if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3) {
            cin.clear(); // Clear error flags
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
            cout << "Invalid input. Try again.\n";
        } else {
            break;
        }
    }
}

template<typename T>
// Constructor for X_O_Random_Player
Misere_Tic_Tac_Toe_Random_Player<T>::Misere_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template<typename T>
void Misere_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y) {
    if (countNum % 2 == 0) this->name = name2;
    else this->name = name1;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif // MISERE_TIC_TAC_TOE_H